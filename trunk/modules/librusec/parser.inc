<?php

function pp($s) {  // ParsePrint - печать в текущий файл результат конвертора
  Global $PD;
  if (!isset($PD->noten)) $PD->noten = 0;
  if ($PD->IN['BODY']) $PD->text[$PD->noten] .= $s;
  if ($PD->IN['ANNOTATION']) $PD->ann .= $s;
}

Global $PD, $html1, $html2;
//Трансляция открывающих тэгов fb2 => html. Можно без угловых скобок - добавятся при необходимости.
$html1 = array ('EPIGRAPH' => '<blockquote class="epigraph">', 'TEXT-AUTHOR' => '<blockquote class=book><i>', 'ANNOTATION' => 'h4 class=book', 
'POEM' => '<div class=poem>', 'V' => 'div', 'EMPTY-LINE' => 'br', 'STANZA' => '<div class=stanza>', 'P' => 'p class=book', 
'SUBTITLE' => 'h5 class=book', 'CITE' => 'blockquote class=book', 'STRONG' => 'b', 'EMPHASIS' => 'i', 'STRIKETHROUGH' => 'strike');

//Трансляция закрывающих тэгов fb2 => html. Отсутствующие тут транслируются по предыдущей схеме.
$html2 = array ('EPIGRAPH' => '</blockquote>', 'TEXT-AUTHOR' => '</i></blockquote>', 'EMPTY-LINE' => '-', 'TITLE' => '</h3>', 'SECTION' => '-', 
'POEM' => '</div>', 'STANZA' => '</div>', 'V' => '</div>', 'IMAGE' => '-', 'P'=>'</p>','ANNOTATION' => '</h4>','SUBTITLE' => '</h5>', 'CITE' => '</blockquote>'); 
function libParserStart($parser, $E, $attrs) {
  Global $PD, $html1;
  if ($PD->done) return;
  $E = strtoupper($E); 
   foreach ($attrs as $key => $val) {
     $attrs[$key]='';
     $attrs[strtolower($key)] = strtolower($val);
   }  
  $PD->IN[$E]++;
  $PD->path[] = $E;
  switch($E) {
    case 'FICTIONBOOK': 
      $PD->xl = 'xmlns:l';
      foreach ($attrs as $key => $val) {
        list($s1, $s2) = split(":", $key, 2);
        if ($s2) $PD->xl = "$s2:href";
      }  
    return;
    case 'BODY':
      if ($attrs['name'] == 'notes') $PD->IN['NOTES'] = 1;
      if ($PD->format == 'head' || $PD->format == 'fbd-head') $PD->done = 1;
    return;
    case 'ANNOTATION':
     return;
    case 'BINARY': 
      if (!$PD->imagefile = $attrs['id']) {
        $PD->imagefile = 'cover.jpg';
        if (!$PD->cover) $PD->cover = "cover.jpg";
      }  
    return;  
    case 'IMAGE': 
      $img = $attrs[$PD->xl];
      if (!$img) $img = $attrs['l:href'];
//      GLOBAL $user; if ($user->uid == 1 && !$img) {print "<pre>$img\n";print_r ($attrs); print_r($PD);exit;}
      if (!$img) return;
      if (preg_match('/^#(.+)/', $img, $m)) { //картинка внутри файла
        $img = $m[1];
        if ($PD->format == 'htm' || $PD->format == 'fbd') $img = "/i/".($PD->b%100)."/$PD->b/$img";
      } 
      if ($img == $PD->cover) return; // обложку не повторяем
      if ($PD->format == 'txt') pp(" [Картинка: $img] ");
      else pp("<img border=0 style='spacing 9px;' src=\"$img\">");
      if ($PD->IN['COVERPAGE']) $PD->cover = $img;
    return;  
   case 'PUBLISH-INFO':
      $PD->seqlevel = 100;
   break; 
   case 'TITLE-INFO':
      $PD->seqlevel = 0;
   break; 
   case 'SEQUENCE':
      $PD->seqlevel++;
      $seqn = $attrs['number'];
      $seqid = AddSeqId($attrs['name']);
      $PD->SeqIds[] = array($seqid, $seqn, $PD->seqlevel);
    return;  
  }
    
//  if (!$PD->IN['BODY']) return;
  if ($PD->format == 'txt') {
    if ($E == 'EMPTY-LINE') pp("\n");
    if ($E == 'P') pp("\n   ");
    return;
  }
  switch ($E) {
    case 'A':  
      foreach ($attrs as $key => $val) {
        if ($val) {
          if ($key == 'type') $atype = $val;
          if ($key == $PD->xl || $key == 'l:href') $adest = $val;
          $la .= ' '.$key.' = "'.$val.'"';
        }  
      }  
      if (strtolower($atype) == 'note') { //ссылка на примечание 
        $PD->noten++;
        $PD->RevLink[$adest] = $PD->noten;
        $PD->notelink = 1;
      } else { // ссылка. просто ссылка.
        $PD->notelink = 0;
        pp("<a $la>");
      }
    break;
    case 'SECTION':
      if ($PD->SectionID = $attrs['id'])      
        pp("<a name=\"$PD->SectionID\"></a>"); 
    break;
    case 'TITLE':   
      if ($PD->IN['SECTION'] && !$PD->SectionID) {
          $PD->tocn++;
          pp("<a name=t$PD->tocn></a><h3 class=book>");
          $PD->TOC .= "<li>";
          for ($i = 1; $i < $PD->IN['SECTION']; $i++) $PD->TOC .= ' &nbsp; ';
          $PD->TOC .= "<a href=#t$PD->tocn>";
      } else pp('<h3 class=book>');  
    break;
    case 'P':
      if (!$PD->IN['TITLE'])
        pp("<p class=book>");
    break;
    default:
      if ($t = $html1[$E]) {
        if ($t[0] != '<') $t = "<$t>";
        pp ($t);
      }  else { //неизвестный науке тэг, оставляем как есть со всеми параметрами
        pp("<$E");
        foreach ($attrs as $key => $val) if ($val) pp (' '.$key.' = "'.$val.'" ');
        pp('>');
      }  
     break;  
  }
}

function libParserEnd($parser, $E) {
  Global $PD, $html1, $html2;
  if ($PD->done) return;
  array_pop($PD->path);
  switch ($E = strtoupper($E)) {
    case 'AUTHOR':
    if ($PD->path[2] == 'TITLE-INFO') { 
      $pp = 'FICTIONBOOK/DESCRIPTION/TITLE-INFO/AUTHOR/';
      $PD->AvtorIds[] = AddAvtorId($PD->head[$pp.'FIRST-NAME'], $PD->head[$pp.'MIDDLE-NAME'], $PD->head[$pp.'LAST-NAME'], $PD->head[$pp.'NICK-NAME']);
      unset($PD->head[$pp.'FIRST-NAME'], $PD->head[$pp.'MIDDLE-NAME'], $PD->head[$pp.'LAST-NAME'], $PD->head[$pp.'NICK-NAME']);
    } 
    break;
    case 'TRANSLATOR':
    if ($PD->path[2] == 'TITLE-INFO') { 
      $pp = 'FICTIONBOOK/DESCRIPTION/TITLE-INFO/TRANSLATOR/';
      $PD->TranslatorIds[] = AddAvtorId($PD->head[$pp.'FIRST-NAME'], $PD->head[$pp.'MIDDLE-NAME'], $PD->head[$pp.'LAST-NAME'], $PD->head[$pp.'NICK-NAME']);
      unset($PD->head[$pp.'FIRST-NAME'], $PD->head[$pp.'MIDDLE-NAME'], $PD->head[$pp.'LAST-NAME'], $PD->head[$pp.'NICK-NAME']);
    } 
    break;
    case 'BINARY':
      $subdir = 'i/'.($PD->b % 100);
      if (!file_exists($subdir) && !mkdir($subdir)) return;
      $dir = $subdir.'/'.$PD->b;
      if (!file_exists($dir) && !mkdir($dir)) return;
      $fh = fopen($dir.'/'.$PD->imagefile, 'w');
      fwrite($fh, base64_decode($PD->data));
      fclose($fh);
      $PD->data = '';
    return;
    case 'FICTIONBOOK':
    return;
    case 'BODY':
      if ($PD->IN['NOTES']) $PD->IN['NOTES'] = '';
      $PD->IN['BODY'] = '';
    return;
    case 'HEAD':
      if ($PD->format == 'head' || $PD->format == 'fbd-head')
        $PD->done = 1;
    case 'ANNOTATION':
      if ($PD->format == 'annotation')
        $PD->done = 1;
  }
  $PD->IN[$E]--;
  if ($PD->format == 'txt') return;
  if ($E == 'SECTION' && $PD->SectionID) {    
    $noten = $PD->RevLink[$adest='#'.$PD->SectionID];
//    global $user; if (!$noten && $user->uid == 1) {print "<pre>"; print_r ($PD); exit;}
    pp(" <small>(<a href=#r$noten>обратно</a>)</small>");  
    $note = addslashes($PD->note);
    $PD->text[$noten-1] .= "<sup><a name=r$noten><a href=\"$adest\" title=\"".str_replace('"', '&quot;', $PD->note)."\">";
  }
  if ($E == 'A' && $PD->notelink) pp('</sup>'); 
  if ($E == 'TITLE' && $PD->IN['SECTION'] && !$PD->SectionID) $PD->TOC .= "</a>";
  if ($E == 'P' && $PD->IN['TITLE']) return;
  $t = $html2[$E];
  if ($t == '-' || $t == 'BR') return;
  if (!$t) $t = $html1[$E];
  if (!$t) $t = $E;
  if ($t != "\n" && $t[0] != '<') $t = "</$t>";
  pp ($t);
}

function libParserData($parser, $E) {
  Global $PD;
  if ($PD->done) return;

  if ($PD->IN['BINARY']) {
    $PD->data .= $E;
    return;
  }  
  $E = str_replace('>','&gt;',$E);
  $E = str_replace('<','&lt;',$E);
  if ($PD->IN['NOTES']) {
    if ($PD->IN['TITLE']) $PD->note = '';  
    else $PD->note .= $E;  
  } else {
    if ($PD->IN['TITLE'] && $PD->IN['SECTION']) 
    $PD->TOC .= $E;
  }  
  if ($PD->IN['DESCRIPTION']) {
    $p = join('/',$PD->path);
    if ($PD->head[$p] || $E != ' ' && $E != "\n")
    if (strstr($p, 'AUTHOR')) {
      $PD->head[$p] = $E; 
    } elseif (strstr($p, 'ANNOTATION') ) {
      $PD->head[$p] .= $E; 
     } else {
      if ($PD->head[$p] && $E != ' ' && !$PD->IN['BOOK-TITLE']) $PD->head[$p] .= ',';
      $PD->head[$p] .= $E; 
    }  
  }  
  if ($PD->format == 'txt') $E = rtrim($E);
  pp($E);
}

function libRead($b) {
  $filetype = Sel("FileType FROM libbook WHERE BookId = $b");
  if ($filetype != 'fb2') {
  	$fbd = libGetFBD("b.usr/".Sel("FileName FROM libfilename WHERE BookId = $b"));
  } else {
  	$fb2 = getfb2filepath($b);
  }
  
  $html = "b.htm/$b.htm";
  
  if (SuperUser() || !file_exists($html)) {
    $key = sem_get(14, 1, 0666, 1);
    if (!sem_acquire($key)) {
    	return;
    }

    if (SuperUser() || !file_exists($html)) {
      if ($fb2) {
        $err = parsefb2($fb2, $b, 'htm', $html);
      } else {
        $err = parsefb2($fbd, $b, 'fbd');
        touch($html);
      }
      if (!$err) {
        Global $PD;
        db_query("INSERT INTO libcache (BookId, TOC, Cover) 
              VALUES (%d, '%s', '%s') ON DUPLICATE KEY UPDATE TOC='%s', Cover='%s'", $b, $PD->TOC, $PD->cover, $PD->TOC, $PD->cover);
        if ($PD->ann && !Sel("nid FROM node WHERE type = 'bdesc' AND title = $b") && !Sel("nid FROM libbnode WHERE BookId = $b")) {
          $body = addslashes($ann = $PD->ann);
          $nid = max (Sel ("MAX(nid) FROM node"), Sel ("MAX(nid) FROM node_revisions")) + 1;
          $vid = max (Sel ("MAX(vid) FROM node"), Sel ("MAX(vid) FROM node_revisions")) + 1;
          $now = time();
          db_query("Insert into node (nid, vid, type, title, uid, status, created, changed, comment, promote, moderate, sticky)
                    VALUES ($nid, $vid, 'bdesc', $b, 5, 1,  $now, $now,     2, 0, 0, 0)");  
          db_query("Insert into node_revisions (nid, vid, uid, title, body, timestamp, format)
                    VALUES ($nid, $vid, 5, $b, '$body', $now, 1)");
         }           
      }
    }
    sem_release($key);
  } 
  return $err.file_get_contents($html);
}
  
function parsefb2($fb2, $b, $format, $tofile = '') {
  unset ($GLOBALS['PD']);
  Global $PD; 
  $PD->format = $format;
  $PD->b = $b;
  $xml_parser = xml_parser_create();
  xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 0);
  xml_set_element_handler($xml_parser, libParserStart, libParserEnd);
  xml_set_character_data_handler($xml_parser, libParserData);
  if ($format == 'fbd-head' || $format == 'fbd') {
    xml_parse($xml_parser, $fb2);
  } else {  
    if (!$fp = fopen($fb2, "r")) return "Ошибочка: не открылся файлик $fb2"; 
    while (($data = fread($fp, 40960)) && xml_parse($xml_parser, $data) && !$PD->done && !feof($fp));
  }  
  xml_parser_free($xml_parser); 
  if (!$tofile) return;
  
  if (!$fh = fopen($tofile, 'w')) return "Не могу создать файлик $tofile";
  if ($PD->format == 'txt') {
    $PD->text[++$PD->noten] = "\n\nВзято из Флибусты, http://lib.rus.ec/b/$PD->b\n";
    for($i = 0; $i <= $PD->noten; $i++) 
      fwrite($fh, iconv("UTF-8", "Windows-1251//TRANSLIT", $PD->text[$i]));
  } else {     
    if ($PD->format == 'html') fwrite($fh, 
      "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf8'>\n".
      file_get_contents(drupal_get_path('module', 'librusec').'/book.css').
      "<title>".Sel("Title FROM libbook WHERE BookId = $PD->b")." - Флибуста</title>\n</head>\n<body>\n");
    for($i = 0; $i <= $PD->noten; $i++) 
      fwrite($fh, $PD->text[$i]);
    if ($PD->TOC) 
      fwrite($fh, "<br><h3>Оглавление</h3>".$PD->TOC);
    if ($PD->AvtorIds[0] == 5329) 
      fwrite($fh, "\n<br>\nСайт автора <a href=http://lleo.aha.ru>http://lleo.aha.ru</a>\n");  
    if ($PD->format == 'html') 
      fwrite($fh, "\n<hr><div align=right>Взято из Флибусты, <a href=http://lib.rus.ec/b/$PD->b>lib.rus.ec</a></div>\n</body></html>");
  }
  fclose($fh);  
}

function parse_fb2_document_info($f) {
  if ($err = parsefb2($f, 0, 'head')) return $err;
  Global $PD;
  foreach ($PD->head as $i => $value) 
    if ($value)
      $r .= "<li>".strtolower($i)." $value";
  return "<ul>$r</ul>"; 
}

function MakeFile($b, $f, $dtp, $r) {
  $fb2 = getfb2filepath($b);
  switch ($dtp) {
    case 'txt':
    case 'html':
      return parsefb2($fb2, $b, $dtp, $r);
    case 'rtf':
     chdir ('conv');
     exec ('perl fb2_2_rtf.pl "../'.$fb2.'" FB2_2_rtf.xsl "../'.$r.'"');
     chdir ('..');
    return;
//    case 'epub':
//      chdir('conv/fb2docbook');
//      exec('python btransformer.py --config btconfig_default.xml --epub /www/'.$fb2.' "/www/'.$r.'"');
//     chdir ('../..');
//    return;
//    case 'pdb':
//     exec ('conv/iSiloXC "'.$fb2.'" "'.$r.'"');
//    return;
//    case 'rb':
//    case 'pdf':
  }  
}

function libGenerateFB2($b, $fb2) {
return '';
}

function libGetFBD($f) {
  if (pathinfo($f, PATHINFO_EXTENSION) != 'zip') return '';
  if (!is_resource($zip = zip_open($f))) return '';
  while($zip_entry = zip_read($zip)) 
    if (pathinfo(zip_entry_name($zip_entry), PATHINFO_EXTENSION) == 'fbd') 
      return zip_entry_read($zip_entry, zip_entry_filesize($zip_entry));
  return '';    
}

function XMLtag($tags) {
  Static $lastlevel = 0;
  if (!$tags) return '';
  list($tag, $level, $option) = explode(' ', $tags, 3);  
  if ($level != '') $lastlevel = $level;
  else $level = $lastlevel;
  $args = func_get_args();
  array_shift($args); 
  $value = implode($args);
  if (!$value && !$option) return '';
  for ($i = 0; $i < $level; $i++) $s .= ' ';
  if ($option) $option = ' '.$option;
  if ($level >= 4) $value = htmlspecialchars($value);
#  if (SuperUser() && $tags == 'annotation') {print "'$value' '".($level < 3 || $args[1] || $args[2] || $args[3]?1:2)."'";exit;}
  if ($value) return "\n$s<$tag$option>$value".($level < 3 || $tag == 'annotation' || $args[1] || $args[2] || $args[3] ? "\n$s":'')."</$tag>";
  return "\n$s<$tag$option/>";
}

function procanntag($t, $slash) {
  if ($t == 'p' || $t == 'poem' || $t == 'cite' || $t == 'subtitle' || $t == 'empty-line') return "<$slash.$t>";
  if ($t == 'br') return '<empty-line>';
  if ($t == 'ul' || $t == 'ol' || $t == 'li' || $t == 'b' || $t == 'u' || $t == 'i' || $t == 's' || $t == 'center') return "[$slash$t]";
  if ($t == 'strong' || $t == 'em') return "[$slash"."b]";
//  if (SuperUser()) {print $t;exit;}
}

function libFDB($b) {
//  drupal_set_header('Content-Type: text/plain');
  $b1 = S("* FROM libbook WHERE BookId = %d", $b);
  if (!$b) return '';
  if ($b1->FileType == 'fb2') {
    if (!$fh = fopen("b/$b.fb2", 'r')) return "Ошибочка: не открылся файлик b/$b.fb2";
    unset ($GLOBALS['PD']);
    Global $PD; 
    $PD->format = 'head';
    $PD->b = $b;
    $xml_parser = xml_parser_create();
    xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 0);
    xml_set_element_handler($xml_parser, libParserStart, libParserEnd);
    xml_set_character_data_handler($xml_parser, libParserData);
    $data = fread($fh, 40960);
    if (!preg_match('/encoding="(.+)"\?>/', substr($data, 0, 88), $m)) return "encoding не обнаружен.";
    $enc = $m[0];
    return $m[0];
    xml_parse($xml_parser, $data);
    xml_parser_free($xml_parser); 
    if ($stylesheet = strstr($data, '<stylesheet')) 
      if ($pos = strpos($stylesheet, '<description')) {
        $stylesheet = "\n".trim(substr($stylesheet, 0, $pos));
      } else {
        $stylesheet = '';
      }  
//    print "<pre>";  print_r($PD);  exit;
  }
  for ($sth = SELECT("GenreCode FROM libgenre JOIN libgenrelist USING(GenreId) WHERE BookId = %d", $b);$a1 = dbf($sth);)
    $genre .= XMLtag('genre 3', $a1->GenreCode);
  for ($sth = SELECT("SeqName, SeqNumb FROM libseq JOIN libseqname USING(SeqId) WHERE BookId = %d", $b);$a1 = dbf($sth);)
    $sequence .= XMLtag('sequence 3 name="'.htmlspecialchars($a1->SeqName).'" number="'.$a1->SeqNumb.'"', $a1->GenreCode);
  for ($sth = SELECT("* FROM libavtorname JOIN libavtor USING(AvtorId) WHERE BookId = %d", $b);$a1 = dbf($sth);)
    $author .= XMLtag('author 3', 
      XMLtag('first-name 4', $a1->FirstName), 
      XMLtag('middle-name', $a1->MiddleName), 
      XMLtag('last-name', $a1->LastName), 
      XMLtag('nickname', $a1->NickName), 
      XMLtag('home-page', $a1->Homepage), 
      XMLtag('email', $a1->Email), 
      XMLtag('id', $a1->AvtorId) 
  );
  for ($sth = SELECT("* FROM libavtorname JOIN libtranslator ON(AvtorId=TranslatorId) WHERE BookId = %d", $b);$a1 = dbf($sth);)
    $author .= XMLtag('translator 3', 
      XMLtag('first-name 4', $a1->FirstName), 
      XMLtag('middle-name', $a1->MiddleName), 
      XMLtag('last-name', $a1->LastName), 
      XMLtag('nickname', $a1->NickName), 
      XMLtag('home-page', $a1->Homepage), 
      XMLtag('email', $a1->Email), 
      XMLtag('id', $a1->AvtorId) 
  );
  if (!$cover = Sel("Cover FROM libcache WHERE BookId = $b")) {
    $nid = Sel("nid FROM libbnode WHERE BookId = $b");
    if ($nid) $vid = Sel("MAX(vid) FROM node_revisions WHERE nid = $nid");
    if ($vid) $cover = Sel("filepath FROM `upload` JOIN files USING(fid) WHERE `vid` = $vid AND filemime LIKE 'image%'");
  }
  $cover = ltrim($cover, '/');
  if ($cover && file_exists($cover)) {
    $imagetype = pathinfo($cover, PATHINFO_EXTENSION);
    if ($imagetype == 'jpg') $contenttype = 'image/jpeg';  
    else $contenttype = 'image/'.$imagetype;  
//    $coverfile = htmlspecialchars(pathinfo($cover, PATHINFO_BASENAME));
    $coverfile = "cover.$imagetype";
    $binary = 'binary 1 id="'.$coverfile.'" content-type="'.$contenttype.'"';
    $coverpage = XMLtag('coverpage', '<image l:href="#'.$coverfile.'"/>');
  }
  $nl = "\n    ";
  if ($ANNARR = explode("\n", Sel("body FROM node_revisions JOIN libbnode USING(nid) WHERE BookId = %d ORDER BY vid DESC", $b))) {
    foreach($ANNARR as $annstr) {
      $annstr = preg_replace('/<!--break-->/i', '', trim($annstr));
      $annstr = preg_replace('/<(\/?)(\w+)\/?>/ie', 'procanntag("\\2","\\1")', $annstr);
      if ($annstr) {
        if (preg_match('/^(\[\/(\w+)\])/', $annstr, $m)) {
          $annstr = preg_replace('/^(\[\/(\w+)\])/', '', $annstr, 1);
          $ann = preg_replace('/<\/p>$/', "$m[0]</p>", $ann);
        }  
        if (strncmp($annstr, '<p>', 3) && strncmp($annstr, '<P>', 3)) $ann .= "$nl<p>$annstr</p>";
        else $ann .= $nl.$annstr;
      } else {
        $ann .= "$nl<empty-line/>";
      }
    }  
  }    
  $fbd =
  XMLtag('FictionBook 0 xmlns="http://www.gribuser.ru/xml/fictionbook/2.0" xmlns:l="http://www.w3.org/1999/xlink"', $stylesheet,
    XMLtag('description 1', 
      XMLtag('title-info 2', 
        $genre, 
        $author, 
        XMLtag('book-title 3', htmlspecialchars($b1->Title.($b1->Title1?"[$b1->Title1]":''))), 
        XMLtag('annotation', $ann), 
        XMLtag('keywords', $b1->keywords),
        ($b1->Year ? XMLtag("date 3", $b1->Year) : ''),
        $coverpage,
        XMLtag('lang', $b1->Lang),
        XMLtag('src-lang', Sel("SrcLang FROM libsrclang WHERE BookId = %d", $b)),
        $translator, 
        $sequence
      ),
      XMLtag('src-title-info 2'),
      XMLtag('document-info 2', 
        XMLtag('author 3', XMLtag('nickname', 'robot') ),
        XMLtag('program-used'),
        XMLtag('date'),
        XMLtag('src-url'),
        XMLtag('src-ocr'),
        XMLtag('id', "LibrusecId-$b"),
        XMLtag('version', 1),
        XMLtag('history'),
        XMLtag('publisher')
      ),
      XMLtag('publish-info 2'),
      XMLtag('custom-info 2 info-type="librusec-id"', $b)
    )
  );
  if ($b1->FileType != 'fb2') return '<?xml version="1.0" encoding="utf-8"?>'.$fbd.XMLtag($binary, "\n", base64_encode(file_get_contents($cover)));

  $fbz = "b.fbz/$b.fb2.zip";
  $fb2fh = fopen("/tmp/$b.fb2", "w");
  if ($enc != 'utf-8') $fbd = iconv("UTF-8", "Windows-1251//TRANSLIT", $fbd);      
  fwrite($fb2fh, '<?xml version="1.0" encoding="'.$enc.'"?>');
  fwrite($fb2fh, $fbd);
  fwrite($fb2fh, strstr($data, '<body>'));
  while (fwrite($fb2fh, fread($fh, 40960)));
  fclose($fb2fh);
  fclose($fh);
//  system("zip -m $fbz /tmp/$b.fb2");
  return $fbz;
}