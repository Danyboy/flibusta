<?php
include_once drupal_get_path('module', 'librusec') .'/librusec.inc';

function libPolka() {
  Global $user, $ButtonStyle;
  if (arg(1) == 'show' && arg(2) == 'all')
    if (arg(3) == 'rss') return libPolkaShowAllRSS();
    else return libPolkaShow('all');
  $u = $user->uid;
  if (!$u || !user_access('пользоваться полкой')) 
    return "У вас нет доступа к книжной полке. Извините.";

  $r = "<a href=/polka/rated>Оценки</a> &nbsp; <a href=/polka/readed>Прочитано</a> &nbsp; <a href='/polka'>Впечатления</a> &nbsp; <a href=/polka/friends>Единомышленники</a> &nbsp; <a href=/polka/friends/books>Советы единомышленников</a> &nbsp; <a href=/polka/watch>Наблюдаемые книги</a><br><br>";


  switch (arg(1)) {
  	case 'watch':
  	  return $r.libBookWatch($u);
    case readed:
      return $r.libPolkaReaded($u);
    case rated:
      return $r.libPolkaRated($u);
    case 'friends':
      if (arg(2) == 'books')
        return $r.libPolkaFriendsBooks();
     return $r.libPolkaFriends();
    case 'show': 
     return libPolkaShow(arg(2));
    case 'add':
      if (($b = 1*arg(2)) && $u) {
        $b = Sel ("BookId FROM libbook WHERE BookId = $b");
        $txt = addslashes($_POST['text']);
        $f = $_POST['Flag'] == 'true' ? 'h' : '';
        if (Sel ("ID FROM libpolka WHERE BookId = $b AND Userid = $u")) 
          Update ('libpolka',"Text = '$txt', Flag='$f'", "BookId = $b AND Userid = $u");
        else 
          Insert ('libpolka', 'BookId, UserId, Text, Flag', "$b, $u, '$txt', '$f'");
        libsettag(polka);  
      }
    break;
    case 'del':
      if (($b = 1*arg(2)) && $u) {
        Delete('libpolka WHERE UserId = %d AND BookId = %d', $u, $b);
        libsettag(polka);  
      }  
    break;
    case 'delrd':
      if (($b = 1*arg(2)) && $u) 
        Delete('libreaded WHERE UserId = %d AND BookId = %d', $u, $b);
    return $r.libPolkaReaded($u);
    case 'hide':
      if (user_access('библиотекарь'))
        Update('libpolka', 'Flag="H"', 'ID = %d', arg(2));
    break;  
  }

  $r .= "<h3>Отложенные книги и комментарии к ним</h3>\n";
  $sth = SELECT ("* FROM libpolka WHERE UserId = $u ORDER BY 1 DESC");
  while ($a1 = dbf($sth)) {
    $b = $a1->BookId;
    $t = stripslashes($a1->Text);
    $ch = $a1->Flag == 'h' ? 'checked' : '';
    $r .= "<br>".DoLibRow($b, 'rate author');
    $r .= "<textarea class=polka cols=80 rows=7 id=$b onchange=polkasave($b) onBlur=polkasave($b)>$t</textarea><br>
        <a href=javascript:polkasave($b)>(записать)</a> 
        <input id=h$b type=checkbox $ch onchange=polkasave($b) onBlur=polkasave($b)> спрятать 
        <a href=/polka/del/$b>(удалить)</a><hr>\n";
  }  

  return $r;
}

function polkaul($u) {
	$name = Sel("name FROM users WHERE uid = '$u'");
	if(!$name) {
		$name = 'Кто-то';
	}

	return bwlist_icons($u)."<b><a href=/polka/show/$u>".$name."</a></b>";
}

function buildForeignUserName($name, $srcid, $link) {
	if(!$name) {
		$name = 'Кто-то';	
	}
	
	$source = getSourceDescription($srcid);
	
	if($link) {
		return "<b>$name (<a href=$source[1]>".$source[0]."</a>)</b>";
	} else {
		return "$name ($source[0])";
	}
}

// функция, отображающая один отзыв
function libpline($a1, $u='', $rss=0) {
	
	if (!bwlist_see($a1->UserId)) {
		return '';
	}

	Global $user, $host;
	
	$b = $a1->BookId;
	$book = Sel("Title FROM libbook WHERE BookId = %d", $b);
	$a = Sel("AvtorId FROM libavtor WHERE BookId = %d", $b);
	$an = $a ? Sel("LastName FROM libavtorname WHERE AvtorId = %d", $a) : '';
	$t = stripslashes($a1->Text);

	// время добавления отзыва по UTC
	if($a1->UserId == 0 && $a1->Source != 0) {
		$tm_stamp = Sel("Time FROM libpolka WHERE Username = '%s' AND BookId = %d AND Source = %d ",$a1->Username,$b,$a1->Source);
	} else {
		$tm_stamp = Sel("Time FROM libpolka WHERE UserId = %d AND BookId = %d",$a1->UserId,$b);
	}
	
	if ($user->uid) {
		$tmz_user = Sel("timezone FROM users WHERE uid = %d", $user->uid); // информация о часовом поясе пользователя, просматривающего страницу
		$tmz_loc = date(Z); // смещение часового пояса сервера в секундах
		$tm = date('H:i / d-m-Y',strtotime($tm_stamp.'-'.$tmz_loc.' seconds '.$tmz_user.' seconds')); // время добавления отзыва вычитаем локальное смещение сервера и добавляем смещение юзера, просматривающего эту страницу
	} else {
		$tm = date('H:i (P) / d-m-Y',strtotime($tm_stamp));
	}
	

	if ($rss) {
		$h = "http://$host";

		if($a1->UserId == 0 && $a1->Source != 0) {
			$username = buildForeignUserName($a1->Username, $a1->Source, 0); 
		} else {
			$username = Sel("name FROM users WHERE uid = %d", $a1->UserId);
			if(!$username) {
				$username = 'Кто-то';
			}
		}

		return "$username про $an: $book\n$t\n";
	} elseif ($u) {
		if($a1->UserId == 0 && $a1->Source != 0) {
			$username = buildForeignUserName($a1->Username, $a1->Source, 1)." про ";
		} else {
			$username = polkaul($a1->UserId)." про ";
		}
		
	}
	
	if (user_access('библиотекарь') && $a1->Id) {
		$hide = " <a href=/polka/hide/$a1->Id>(спрятать)</a>";	
	}
	
	$t = preg_replace('/\n/', '<br>', $t);
	$sth = SELECT("* FROM libgenre JOIN libgenrelist USING(GenreId) WHERE BookId = %d", $b);
	
	while ($a1 = dbf($sth)) {
		if ($g) $g .= ', ';
		$g .= "<a name=$a1->GenreCode><a href=/g/$a1->GenreCode>$a1->GenreDesc</a>";
	}
	if ($g) {
		$g = " ($g)";	
	}
	
	return "$username <a href=\"$h/a/$a\">$an</a>: <a href=\"$h/b/$b\">$book</a>$g в $tm$hide<br>$t<hr>\n";
}

function libPolkaShow($u) {
	Global $user, $rates;
	
	if ($u == 'all') {
		drupal_set_html_head('<link rel="alternate" type="application/rss+xml" title="Новые впечатления на Флибусте RSS" href="/polka/show/all/rss" />');
		set_title("<a href='/polka/show/all/rss' class='feed-icon'><img src='/misc/feed.png' alt=RSS title='RSS' width='16' height='16'></a>&nbsp;Впечатления о книгах");
		
		if ($user->uid) {
			$mode = Sel("bw FROM {bwlist} WHERE uid = %d AND uid2 = 0", $user->uid);
			$gg = libListBlackGG();
		}
		
		$cid = md5("pall$u.$gg.p".$_GET['page'].($mode?'':"uu".$user->uid)).user_access('библиотекарь');
		if ($r = libcg($cid)) {
			return $r;	
		}
		
		$fields = "BookId, libpolka.UserId AS UserId, Text, Time, Username, Source ";
		if ($gg) {
			if (!$_GET['page']) $limit = "libpolka.ID > 44000 AND ";
			else $limit = "libpolka.ID > 30000 AND ";
			$where = "LEFT JOIN libgenre USING(BookId) LEFT JOIN libuserblackgenre bg USING(GenreId) WHERE $limit (isnull(bg.UserId) OR bg.UserId != $user->uid) AND";
			$group = "GROUP BY libpolka.ID";
		} else {
			$where = "WHERE";
		}
		
		$S = "FROM libpolka $where Flag = '' AND Text <> ''";
		if ($mode == 'w') {
			$S = "FROM libpolka JOIN {bwlist} ON (libpolka.UserId=uid2) $where uid='$user->uid' AND bw='w' AND Flag = '' AND Text <> ''";
		} elseif ($mode == 'b') {
			$bl .= bwlist_makewhere('libpolka.UserId');
			if ($bl) $S = "FROM libpolka $where $bl AND Flag = '' AND Text <> ''";
		}
		
		$sth = pgq("SELECT $fields, libpolka.ID AS Id $S $group ORDER BY libpolka.Time DESC", 10000);
//		$sth = pgq("SELECT $fields, libpolka.ID AS Id $S $group ORDER BY libpolka.ID DESC", 10000); //Sel ("COUNT(*) $S")
		while ($a1 = dbf($sth)) {
			if ($tm = ptm($a1->Time)) {
				if ($r) {
					$r .= '<br>';	
				}
				$r .= "<h4>$tm</h4><br>\n";
			}
			$r .= libpline($a1, 1);
		}
		
		return libcs($cid, libListBlackGenre().$r."<br>".theme('pager'), 'polka');
	}

	if ($u) $u = Sel("uid FROM users WHERE uid = '$u' OR name = '$u'");
	if (!$u) return "Пользователь $u не найден.";

	set_title(Sel("name FROM users WHERE uid = '$u'")." - книжная полка");
	$sth = SELECT("* FROM libpolka WHERE libpolka.UserId = $u AND Flag = '' AND Text <> '' ORDER BY ID DESC");
	while ($a1 = dbf($sth)) $r .= libpline($a1);
	$r .= "<br><h3>Оцененные книги</h3>\n<table>\n";
	$sth = SELECT ("BookId, Rate FROM librate WHERE UserId = $u ORDER BY Rate DESC");
	while ($a1 = dbf($sth)) $r .= "<tr><th>$a1->Rate (".$rates[$a1->Rate].") &nbsp; <td>".DoLibRow($a1->BookId, 'rate nobreak author')."\n";
	$r .= "</table>\n";
	return libListBlackGenre().$r;
}

function libPolkaFriends() {
  Global $user; 
  set_title("Читатели со схожими вкусами");
  if (!$u = $user->uid) return "Данный сервис имеет смысл только для зарегистрированных пользователей"; 
  $r = "<table><tr><th>Читатель<th>Похожих оценок";
  $sth = SELECT ("SUM(1) AS s, l2.UserId AS u FROM librate AS l1 JOIN librate AS l2 
         WHERE l1.UserId = $u AND l2.UserId <> $u AND l2.BookId = l1.BookId AND ABS(l1.rate-l2.rate) < 2 
         GROUP BY 2 ORDER BY 1 DESC LIMIT 100");
  while ($a1 = dbf($sth)) $r .= "\n<tr><td>".polkaul($a1->u)."<td>$a1->s";
  return $r."</table>\n";
 }
 
function libPolkaFriendsBooks() {
  Global $user; 
  set_title("Рекомендации друзей");
  if (!$u = $user->uid) return "Данный сервис имеет смысл только для зарегистрированных пользователей"; 
  $r = "<table><tr><th><th>Книга<th>Хороших оценок";
  $sth = SELECT ("SUM(1) AS s, l2.UserId AS u FROM librate AS l1 JOIN librate AS l2 
         WHERE l1.UserId = $u AND l2.UserId <> $u AND l2.BookId = l1.BookId AND ABS(l1.rate-l2.rate) < 2 
         GROUP BY 2 ORDER BY 1 DESC LIMIT 50"); // люди с похожими вкусами

  if (Sel('GenreId FROM libuserblackgenre WHERE UserId=%d LIMIT 1', $u)) {
    $BGLIST = "JOIN libgenre USING(BookId) WHERE NOT EXISTS(SELECT UserId FROM libuserblackgenre bg WHERE UserId = $u AND libgenre.GenreId = bg.GenreId) AND";
  } else {
    $BGLIST = "WHERE";
  }

  while ($a1 = dbf($sth)) {
    $f = $a1->u;
    $totrated = Sel("SUM(1) FROM librate AS l1 JOIN librate AS l2 
                WHERE l2.BookId = l1.BookId AND l1.UserId = $u AND l2.UserId = $f"); // всего оценено товарищем $f из оценненых $u
    if ($totrated && $a1->s/$totrated > 0.7) $FRIENDS[$f] = $a1->s/$totrated;//определяем степень похожести, меньше 70% - это уже не единомышленник ниразу;
  }
  if (!$FRIENDS) return "Друзья не обнаружены. Оцените больше книг.";
  arsort($FRIENDS); // сортируем по похожести.
  while (list($f, $v) = each($FRIENDS)) {
    $sth = SELECT ("BookId, Rate-3 as r FROM librate $BGLIST UserId = $f AND Rate > 3");
    while ($a1 = dbf($sth)) 
      if (!$skipbook[$b = $a1->BookId]) {
        $wst = libWST($b);
        if (Sel ("BookId FROM libreaded WHERE UserId = $u AND $wst") OR libGetRate($b) OR !Sel("BookId FROM libbook WHERE BookId = $b")) {
          $skipbook[$b] = 1; // это мы уже читали
        } else {
          $BOOKS[$b] += $a1->r*3*$v*$v;  
          $RECOM[$b] ++;
        }  
      }
  }
  
  arsort($BOOKS);
  for ($i = 0; $i < 100 && (list($b, $v) = each($BOOKS)); $i++) 
    $r .=  "<tr><td>".DoLibRow($b, 'rateonly')."<td><a href=/b/$b>".DoLibRow($b, 'author')."</a><td>".$RECOM[$b]."\n";
  return $r."</table>\n";
}
 
function libPolkaReaded($u) {
  $r .= "<br><br><h3>Прочитанные неоценённые книги</h3>\n<ol>\n";
  if ($oo = $_GET['order']) SetUserOpt('p',$oo);
  else $oo = GetUserOpt('p');
  switch ($oo) {
    case 'a':
      $join = 'JOIN libavtor USING(BookId) JOIN libavtorname USING(AvtorId)';
      $order = 'LastName, FirstName';
      $g = "GROUP BY 1";
      $c1 = 'checked';
    break;  
    case 'n':
      $join = 'JOIN libbook USING(BookId)';
      $order = 'Title';
      $c2 = 'checked';
    break;  
    case 'p':
      $join = 'JOIN libbook USING(BookId)';
      $order = 'N DESC';
      $c4 = 'checked';
    break;  
    default:
      $order = 'Time DESC';
      $c3 = 'checked';
    break;  
  }
  $r .= "Сортировать: <form action=/polka/readed>
  <input type=radio name=order value=a $c1 onchange='this.form.submit()'>По автору 
  <input type=radio name=order value=n $c2 onchange='this.form.submit()'>По названию 
  <input type=radio name=order value=t $c3 onchange='this.form.submit()'>По времени прочтения
  <input type=radio name=order value=p $c4 onchange='this.form.submit()'>По популярности
  </form>";
  $sth = pgq("SELECT BookId FROM libreaded LEFT JOIN librate USING (UserId, BookId) $join 
              WHERE UserId = $u AND ISNULL(rate)  
              ORDER BY $order", Sel ("COUNT(*) FROM libreaded WHERE UserId = $u"));
  while ($b = db_result($sth)) {
    if (Sel ("rate FROM librate WHERE BookId = $b AND UserId = $u")) continue;
    if ($c1) {
      $a = Sel ("AvtorId FROM libavtor WHERE BookId = $b");
      if ($a != $oa) {
        $r .= "<h4>".avl($a)."</h4>";
        $oa = $a;
      }  
    }    
    $r .= "<li>".DoLibRow($b, 'rate nobreak author')." <a href=/polka/delrd/$b>(не читал)</a>\n";
  } 
  $r .= "</ol>\n";  
  return $r.theme('pager');
}

function libPolkaRated($u) {
  $r .= "<br><br><h3>Оценки</h3>\n<ol>\n";
  if ($oo = $_GET['order']) SetUserOpt('p',$oo);
  else $oo = GetUserOpt('p');
  switch ($oo) {
    case 'a':
      $join = 'JOIN libavtor USING(BookId) JOIN libavtorname USING(AvtorId)';
      $order = 'LastName, FirstName';
      $g = "GROUP BY 1";
      $c1 = 'checked';
    break;  
    case 'n':
      $join = 'JOIN libbook USING(BookId)';
      $order = 'Title';
      $c2 = 'checked';
    break;  
    case 'p':
      $join = 'JOIN libbook USING(BookId)';
      $order = 'N DESC';
      $c4 = 'checked';
    break;  
    default:
      $order = 'ID DESC';
      $c3 = 'checked';
    break;  
  }
  $r .= "Сортировать: <form action=/polka/rated>
  <input type=radio name=order value=a $c1 onchange='this.form.submit()'>По автору 
  <input type=radio name=order value=n $c2 onchange='this.form.submit()'>По названию 
  <input type=radio name=order value=t $c3 onchange='this.form.submit()'>По времени прочтения
  <input type=radio name=order value=p $c4 onchange='this.form.submit()'>По популярности
  </form>";
  $sth = pgq("SELECT BookId FROM librate $join WHERE UserId = $u $g ORDER BY $order", Sel ("COUNT(*) FROM librate WHERE UserId = $u"));
  while ($b = db_result($sth)) {
    if ($c1) {
      $a = Sel ("AvtorId FROM libavtor WHERE BookId = $b");
      if ($a != $oa) {
        $r .= "<h4>".avl($a)."</h4>";
        $oa = $a;
      }  
    }    
    $r .= "<li>".DoLibRow($b, 'rate nobreak author')."\n";
  } 
  $r .= "</ol>\n";  
  return $r.theme('pager');
}

function libPolkaShowAllRSS($a=0) {
	Global $host;
	$CacheFile = "cache/p/$a.rss";
	
	if ($fh = libOpenCacheFile($CacheFile, 3600*$hours)) {
		$host = preg_replace('/^www./','',$_SERVER['HTTP_HOST']);
		if ($host == 'proxy.flibusta.net' or $host == '93.174.93.47') {
			$host = 'flibusta.net';
		}
				
		$link = "<link>http://$host/polka/show/all</link>";
		
		if ($a > 0) {
			$link = "<link>http://$host/a/$a/v</link>";	
		}
		
		fwrite($fh, '<?xml version="1.0" encoding="utf-8"?>
							<rss version="2.0">
								<channel>
									<title>Новые впечатления на Флибусте</title>'." 
								$link
									<description>Последние 50 впечатлений о книгах на Флибусте</description>");
								
		if ($a > 0) {
			$sth = SELECT ("libpolka.BookId AS BookId, UserId, Text, Username, Source, CONCAT(DATE_FORMAT(Time, '%a, %e '), LEFT(DATE_FORMAT(Time, '%M'),3), DATE_FORMAT(Time, ' %Y %T')) AS T
      			FROM libpolka JOIN libavtor USING (BookId) WHERE libavtor.AvtorId = $a AND Flag = '' AND Text <> '' ORDER BY libpolka.ID DESC LIMIT 50");
		} else {
			$sth = SELECT ("BookId, UserId, Text, Username, Source, CONCAT(DATE_FORMAT(Time, '%a, %e '), LEFT(DATE_FORMAT(Time, '%M'),3), DATE_FORMAT(Time, ' %Y %T')) AS T
      			FROM libpolka WHERE Flag = '' AND Text <> '' ORDER BY ID DESC LIMIT 50");
		}
		
		while ($a1 = dbf($sth)) {
			$an = libpline($a1, 1, 1);
			$book = Sel("Title FROM libbook WHERE BookId = $a1->BookId");
			fwrite($fh, format_rss_item($book, "http://$host/b/$a1->BookId", $an,
			array('guid' => "http://$host/b/$a1->BookId/$a1->UserId", 'pubDate' => "$a1->T GMT")));
		}
		fwrite($fh, "</channel>\n</rss>\n");
		fclose($fh);
	}
	
	ob_clean();
	header('Content-Type: application/rss+xml; charset=utf-8');
	echo libReadCacheFile ($CacheFile);
	exit;
}

function libBookWatch($u) {
  switch(arg(2)) {
    case 'add':
      $id = addslashes(arg(3));
      if (!$id) $id = addslashes($_POST['id']);
      if (!($id = Sel("BookId FROM libbook WHERE BookId = %d", $id)))
        $r .= "<b style='color:red;'>Нет такой книги.</b><br><br>";
      else {
        Insert('libbookwatch', 'UserId, BookId', "$u, $id");
        $r .= "<span style='color:green;'>Книга $id добавлена в список наблюдения.</span><br><br>";
      }
      break;
    case 'del':
      $id = addslashes(arg(3));
      if (!($id = Sel("BookId FROM libbookwatch WHERE BookId = %d", $id)))
        $r .= "<b style='color:red;'>Нет такой книги в списке наблюдения.</b><br><br>";
      else {
        Delete("libbookwatch WHERE UserId = %d AND BookId = %d", $u, $id);
        $r .= "<span style='color:green;'>Книга $id удалена из списка наблюдения.</span><br><br>";
      }
      break;
  }
  $r .= "<h3>Наблюдаемые книги</h3>";
  $r .= "<br><form method=POST action=/polka/watch/add>BookId: <input name=id size=15/>&nbsp;<input type=submit value='Добавить'/></form><br>";
  $sth = SELECT ("b.BookId, Title, Deleted FROM libbookwatch bw, libbook b WHERE bw.UserId = %d AND bw.BookId = b.BookId", $u);
  while ($a1 = dbf($sth)) {
    $r .= "<a href=/polka/watch/del/$a1->BookId>[-]</a>&nbsp;<a href=/b/$a1->BookId>$a1->Title</a>";
    if ($a1->Deleted & 1) {
      $goodid = Sel("GoodId FROM libjoinedbooks WHERE BadId = %d", $a1->BookId);
      if (!$goodid)
        $r .= " - удалена";
      else {
        $title2 = Sel("Title FROM libbook WHERE BookId = %d", $goodid);
        $r .= " - заменена на <a href=/b/$goodid>$title2</a>";
      }
    }
    $r .= "<br>";
  }
  return $r;
}
