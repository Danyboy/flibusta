<?php
error_reporting(E_ERROR | E_WARNING | E_PARSE);
$t1 = microtime(TRUE);
Global $DBH, $u, $m;
require_once ('./sites/default/settings.php'); //тут лежат логины к мускулу
function variable_get($name, $default) {  global $conf;  return isset($conf[$name]) ? $conf[$name] : $default;}
$memcachemodule = 'modules/memcache/dmemcache.inc';
if (file_exists($memcachemodule)) require_once ($memcachemodule);
else $memcachemodule = '';
preg_match('|://(.+)@(.+)/(.+)$|',$db_url, $m);  //разбираем в поисках логина к базе.
$up = split(':', $m[1]);  //user:pwd
$DBH = mysql_connect($m[2], $up[0], $up[1]) or die("Could not connect: " . mysql_error()); 
mysql_select_db($m[3],  $DBH) or die(mysql_error());
mysql_query("SET CHARSET utf8");
mysql_query("SET NAMES utf8");
function Insert($tbl, $col, $val) { return mysql_query("INSERT INTO $tbl ($col) values ($val)");}
function SELECT($st) { return mysql_query("SELECT $st");}
function Sel($st) { return ($sth = SELECT($st)) && mysql_num_rows($sth) > 0 ? mysql_result($sth, 0) : ''; }
function Update ($table, $columns, $cond) { return mysql_query("UPDATE $table SET $columns WHERE $cond");}
function dbf ($s)     {return mysql_fetch_object($s);}
function S($st)       {return dbf(SELECT($st));}
function SQLRows($st) {return mysql_num_rows(SELECT($st));}
function p($t) { return addslashes(trim(urldecode($_GET[$t])));}

function AvtorName($a, $t=' ') {
  $an = Sel ("CONCAT_WS('$t', FirstName, MiddleName, LastName) from libavtorname WHERE AvtorId = $a");
  $nick = Sel ("NickName from libavtorname WHERE AvtorId = $a");
  if ($nick) $an .= " ($nick)";
  $an = preg_replace('/>/','&gt;',$an);
  $an = preg_replace('/</','&lt;',$an);
  return $an;
}

function avl($a, $t=' ', $o='') {  
  $cnt = '';
  if ($o === cnt) $cnt = '('.Sel("count(*) FROM libbook JOIN libavtor USING(BookId) WHERE AvtorId = $a AND NOT (Deleted&1)").')'; 
  return "<a href=/av?$a>".AvtorName($a, $t)."</a>$cnt"; 
}

function createBookSourceCopy($bookId, $state, $source) {

	if($state == -1) {
		$result = mysql_query("SELECT State, Source from libbook WHERE BookId = $bookId");
		$book = mysql_fetch_object($result);

		$state = $book->State;
		$source = $book->Source;
	}

	if($state == 0) {
		mysql_query("INSERT INTO libbook_sync SELECT BookId,FileSize,Time,Title,Title1,Lang,FileType,Year,Deleted,Ver,FileAuthor,N,keywords,md5,Modified,Source FROM libbook WHERE BookID=$bookId");
		mysql_query("UPDATE libbook SET State=1 WHERE BookID=$bookId");

		mysql_query("INSERT INTO libavtor_sync SELECT BookId,AvtorId,$source FROM libavtor WHERE BookID=$bookId");
		mysql_query("INSERT INTO libtranslator_sync SELECT BookId,TranslatorId,$source FROM libtranslator WHERE BookID=$bookId");
		
		mysql_query("INSERT INTO libgenre_sync SELECT BookId,GenreId,$source FROM libgenre WHERE BookID=$bookId");
		mysql_query("INSERT INTO libjoinedbooks_sync SELECT BadId,GoodId,$source FROM libjoinedbooks WHERE BadID=$bookId");
		mysql_query("INSERT INTO libsrclang_sync SELECT BookId,SrcLang,$source FROM libsrclang WHERE BookID=$bookId");
		mysql_query("INSERT INTO libblocked_sync SELECT BookId,block,$source FROM libblocked WHERE BookID=$bookId");
		mysql_query("INSERT INTO libseq_sync SELECT BookId,SeqId,SeqNumb,Level,$source FROM libseq WHERE BookID=$bookId");
	}
}

function createAvtorSourceCopy($avtorId, $state, $source) {

	if($state == -1) {
		$result = mysql_query("SELECT State, Source from libavtorname WHERE AvtorId = $avtorId");
		$avtor = mysql_fetch_object($result);

		$state = $avtor->State;
		$source = $avtor->Source;
	}

	if($state == 0) {
		mysql_query("INSERT INTO libavtorname_sync SELECT AvtorId,FirstName,MiddleName,LastName,NickName,NoDonate,uid,WebPay,Email,Homepage,Source FROM libavtorname WHERE AvtorID=$avtorId");
		mysql_query("UPDATE libavtorname SET State=1 WHERE AvtorID=$avtorId");

		mysql_query("INSERT INTO libavtoraliase_sync SELECT BadId,GoodId,$source FROM libavtoraliase WHERE BadID=$avtorId");
	}
}

     
$u = 0;
foreach ($_COOKIE as $cook) if ($u = Sel("uid FROM sessions WHERE sid = '$cook'")) break;

if ($u) 
  if (Sel( "uid FROM users_roles WHERE uid=$u AND rid=4")) 
    exit;

$uu = $u ? $u : $_SERVER['REMOTE_ADDR'];

if (isset($_GET['b'])) $b = (integer)$_GET['b'];
if (isset($_GET['a'])) $a = (integer)$_GET['a'];
if (isset($_GET['op'])) $op = $_GET['op'];
elseif (isset($_POST['op'])) $op = $_POST['op'];
if (!$op) exit;

switch ($op) {
  case 'topadvert':
    if ($_POST['len'] < 100) { // попытка найти книгу в магазинах не удалась. Вычёркиваем.
      $b = substr($_POST['id'], 19);
      mysql_query("INSERT INTO libtopadvert (BookId) VALUES($b) ON DUPLICATE KEY UPDATE Time = NOW()");
    }
  exit;
  case 'ss':
    if ($b && $uu) 
      db_query("INSERT INTO libreaded (BookId, UserId) VALUES($b, $uu) ON DUPLICATE KEY UPDATE BookId = BookId");    
  exit;

  case 'polka':
    if (!$u) {
    	exit;	
    }
    $b = (integer)$_POST['BookId'];
    $b = Sel ("BookId FROM libbook WHERE BookId = $b");
    $txt = addslashes($_POST['text']);
    $f = $_POST['Flag'] == 'true' ? 'h' : '';
    if ($b > 0 && $u && $txt != 'undefined') { 
        if (Sel ("ID FROM libpolka WHERE BookId = $b AND Userid = $u")) {
            //Update ('libpolka',"Text = '$txt', Flag='$f'", "BookId = $b AND Userid = $u");
			mysql_query("UPDATE libpolka SET Text = '$txt', Flag='$f' WHERE BookId = $b AND Userid = $u");          
        } else { 
			mysql_query("INSERT INTO libpolka (BookId, UserId, Text, Flag) VALUES($b, $u, '$txt', '$f')");          
			//Insert ('libpolka', 'BookId, UserId, Text, Flag', "$b, $u, '$txt', '$f'");
        }
    	
      //mysql_query("INSERT INTO libpolka (BookId, UserId, Text, Flag) VALUES($b, $u, '$txt', '$f') ON DUPLICATE KEY UPDATE Text = '$txt', Flag='$f'");
    }
 exit;

  case 'aname':
    $a = addslashes($_GET['s']);
    $a = Sel ("AvtorId FROM libavtorname WHERE AvtorId='$a' OR LastName='$a' OR '$a'=CONCAT(FirstName,' ',LastName) LIMIT 1"); 
    if ($a) print "$a:".AvtorName($a);
 exit;

  case 'setrate':
    $r = 1*($_GET['r']);
    if (!$b || !$uu || !($r>0)) exit;
    mysql_query("INSERT INTO librate (BookId, UserId, Rate) VALUES($b, $u, $r) ON DUPLICATE KEY UPDATE Rate=$r");
    $cid = "librate$uu";
    if ($memcachemodule) dmemcache_delete($cid, librusec);
    else mysql_query ("DELETE FROM librusec WHERE cid = '$cid'");
 exit;

  case 'setquality':
    $q = 1*($_GET['q']);
    if (!$b || !$u || !$q) exit;
    mysql_query("INSERT INTO libquality (q, BookId, uid) VALUES ($q, $b, $u) ON DUPLICATE KEY UPDATE q=$q");
    $cid = 'libq'.$b;
    if ($memcachemodule) dmemcache_delete($cid, librusec);
    else mysql_query ("DELETE FROM librusec WHERE cid = '$cid'");
 exit;

  case 'setuseropt':
    $o = addslashes($_GET['o']);
    $v = addslashes($_GET['v']);
    if (!$o || !$v || !$u) exit;
    mysql_query("INSERT INTO libuseropt (User, Opt, Value) VALUES($u, '$o', '$v') ON DUPLICATE KEY UPDATE Value = '$v'");
  exit;
 
  case 'getuseropt':
    $o = addslashes($_GET['o']);
    if (!$o || !$u) exit;
    print Sel ("Value FROM libuseropt WHERE User = $u AND Opt = '$o'");
  exit;

  case 'setlang':  
   $l = addslashes($_GET['l']);
   if (!$b || !$l || !$u) {
   	exit;
   }
   $l1 = Sel("Lang FROM libbook WHERE BookId = $b");
   if ($l == $l1) {
   	exit;
   }
   
   createBookSourceCopy($b, -1, 0);
   
   Update ('libbook', "Lang = '$l'", "BookId = $b");
   $un = Sel("name FROM users WHERE uid=$u");
   Insert ('libactions', 'UserName, ActionSQL, ActionDesc, ActionUndo', "\"$un\", \"UPDATE libbook SET Lang = '$l' WHERE BookId = $b\", 
           \"Set lang $l for $b\", \"UPDATE libbook SET Lang = '$l1' WHERE BookId = $b\"");
  exit;

  case 'setyear':  
   $l = (integer) $_GET['l'];
   if (!$b || !$l || !$u) {
   	exit;
   }
   
   createBookSourceCopy($b, -1, 0);
      
   Update ('libbook', "Year = '$l'", "BookId = $b");
   $un = Sel("name FROM users WHERE uid=$u");
   Insert ('libactions', 'UserName, ActionSQL, ActionDesc, ActionUndo', "\"$un\", \"UPDATE libbook SET Year = '$l' WHERE BookId = $b\", 
           \"Set Year $l for $b\", \"UPDATE libbook SET Year = '$l1' WHERE BookId = $b\"");

/*  case 'setyear':  
   $l = (integer) $_GET['l'];
   if (!$b || !$l || !$u) exit;
   Update ('libbook', "Year = '$l'", "BookId = $b");
   $un = Sel("name FROM users WHERE uid=$u");
   Insert ('libactions', 'UserName, ActionSQL, ActionDesc, ActionUndo', "\"$un\", \"UPDATE libbook SET Year = '$l' WHERE BookId = $b\", 
           \"Set Year $l for $b\", \"UPDATE libbook SET Year = '$l1' WHERE BookId = $b\"");
*/
  exit;  
  
  case 'setuid':  

   if (!$a || !$u) exit;
   $l = addslashes($_GET['l']);
   $uid = 0;
   if ($l == '' OR ($uid = Sel ("uid FROM users WHERE name = '$l'"))) {
     $ouid = Sel ("uid FROM libavtorname WHERE AvtorId = $a");
     
     createAvtorSourceCopy($a, -1, 0);
     
     Update ('libavtorname', "uid = $uid", "AvtorId = $a");
     $un = Sel("name FROM users WHERE uid=$u");
     Insert ('libactions', 'UserName, ActionSQL, ActionDesc, ActionUndo', "\"$un\", 'UPDATE libavtorname SET uid = $uid WHERE AvtorId = $a', 
           'Set Avtor UID to $uid for $a', 'UPDATE libavtorname SET uid = '$ouid' WHERE AvtorId = $a'");
   }           
   print "uid = $uid";
 exit;
}



