function UCC(xxx) {
  for (i = 1; i < document.forms["bk"].length; i++) {
    var q = document.forms["bk"].elements[i];
    if (q.id != "sa") q.checked = xxx;
  }
}

function UCCg(xxx, g) {
  for (i = 1; i < document.forms["bk"].length; i++) {
    var q = document.forms["bk"].elements[i];
    if (q.id.split('-')[0] == g) q.checked = xxx;
  }
}

function UCCs(xxx, g) {
  for (i = 1; i < document.forms["bk"].length; i++) {
    var q = document.forms["bk"].elements[i];
    if (q.id.split('-')[1] == g) q.checked = xxx;
  }
}

function confirmmassdownload() {
  n = 0;
  f = document.forms["bk"];
  for (i = 1; i < f.length; i++)    
      if (f.elements[i].checked && f.elements[i].name > 0)  n++  
  if (n < 1) return false;
  return confirm("Уверены в необходимости выкачать "+n+" книг одним файлом?");
}

function confirmmassdelete() {
  n = 0;
  f = document.forms["bk"];
  for (i = 1; i < f.length; i++)    
      if (f.elements[i].checked && f.elements[i].name > 0)  n++  
  if (n < 1) return false;
  return confirm("Уверены в необходимости удаления "+n+" книг?");
}

function confirmmassundelete() {
  n = 0;
  f = document.forms["bk"];
  for (i = 1; i < f.length; i++)    
      if (f.elements[i].checked && f.elements[i].name > 0)  n++  
  if (n < 1) return false;
  return confirm("Уверены в необходимости восстаноления "+n+" книг?");
}

function clearchbox() {
  f = document.forms["bk"];
  for (i = 0; i < f.length; i++) 
    if (f.elements[i].name > 0)
      f.elements[i].checked = ""
}

function cnf(ask, todo) {
  if(confirm(ask)) location.href = todo;
}

var ltm = new Array();
var ltxt = new Array();
var ltxt1 = new Array();
var ii=1;

function polkasave(b) {
  if (!(b>0)) return;
  var txt = $("#"+b).val()
  var f = $("#h"+b);
  var ch = f.attr("checked");
  if (ltxt[b] == -1) ltxt[b]=txt+ch;
  if (ltxt[b] == txt+ch) return;  
  ltxt[b]=txt+ch

//  var tm = new Date; tm = tm.getTime()
//  if (tm - ltm[b] < 1111) { setTimeout(polkasave, 444); return; } 
//  ltm[b] = tm

  jQuery.post("/AJAX.php",  { op:'polka', BookId:b, text:txt, Flag:ch}) 
}  

function setrate(b) {
 r = document.getElementById('rate'+b).value;
 jQuery.get('/tools/ajax', {op:'setrate',b:b,r:r}); 
}

function setquality(b) {
 q = document.getElementById('q'+b).value;
 jQuery.get('/tools/ajax', {op:'setquality',b:b,qq:q}); 
}
 
function setuseropt(o) {
 v = document.getElementById('useropt').value;
 jQuery.get('/AJAX.php', {op:'setuseropt',o:o,v:v}); 
}

jQuery(document).ready(function (){$("textarea.polka").each(function(){b=this.id; ltxt[b]=-1; polkasave (b)})})

function setlang(b){
 l = document.getElementById('lang'+b).value;
 jQuery.get('/AJAX.php', {op:'setlang',b:b,l:l}); 
}

function setyear(b){
 l = document.getElementById('year'+b).value;
 jQuery.get('/AJAX.php', {op:'setyear',b:b,l:l}); 
}

function setuid(a){
 l = document.getElementById('uid'+a).value;
 jQuery.get('/AJAX.php', {op:'setuid',a:a,l:l}); 
}

function show(id) {
 el = document.getElementById(id).style;
 if( el.position != 'absolute' ) {
   el.position = 'absolute';
   el.left = '-4000px';
 } else {
   el.position = 'relative';
   el.left = '0px';
 }
}







//код из uscript.js

var flg_c58d3a71 = 0, stm_c58d3a71 = 0, sp0_c58d3a71 = 0, sp1_c58d3a71 = 0;
var cfg_c58d3a71 = null, bmk_c58d3a71 = null, pgp_c58d3a71 = null;
var pgn_c58d3a71 = null, idb_c58d3a71 = '0', ajn_c58d3a71 = null;
var bpd_c58d3a71 = { a:null, c:0, s:'', h:0, b:0 };
var edn_ea29d0c6 = null, bsf_ea29d0c6 = 0, abf_ea29d0c6 = 0;
var gsw_ea29d0c6 = null, mvs_ea29d0c6 = { x:360, y:360, h:0, i:100000 };

try {

	if(window.addEventListener)
		window.addEventListener('DOMContentLoaded', fn00_c58d3a71, false);

	fn39_c58d3a71(window, 'load', fn00_c58d3a71);

	if(document.addEventListener)
		document.addEventListener('load', fn00_c58d3a71, false);

} catch (_err_) {;}

function fn00_c58d3a71()
{
	if(flg_c58d3a71) return;
	flg_c58d3a71 = 1;

	try {

		var n0 = document.getElementById('sidebar-right');
		var n1 = document.getElementById('sidebar-left');
		var n2 = document.getElementById('main');
		if(!n2) n2 = document.getElementById('center');

		var ap = location.pathname.split('/');
		var p1 = (ap[1] || '').toLowerCase();

		cfg_c58d3a71 = fn03_c58d3a71('c58d3a71', 210);

	} catch (_err_) { return; }

	if(ap.length > 3 && p1.charAt(0) == 'b' && fn11_c58d3a71(ap[3], 'read')
		&& !ap[4] && !location.search && n2)
	{
		try {

			bmk_c58d3a71 = fn03_c58d3a71('c58d3a72', 500);
			idb_c58d3a71 = escape(ap[2].toLowerCase());
			var r = fn05_c58d3a71(bmk_c58d3a71, idb_c58d3a71);

			if(r && !isNaN(r = parseInt(r)))
			{
				sp1_c58d3a71 = (document.body.scrollHeight
					* (r / 10000 / 100));
				if(sp1_c58d3a71 > 80) fn09_c58d3a71(r, n2);
			}

			fn56_c58d3a71(n2);

		} catch (_err_) {;}

		var pf = (fn05_c58d3a71(cfg_c58d3a71, 'rps') != '1');

		fn54_c58d3a71(n2, pf);

		if(pf && (n0 || n1))
		{
			if(n0) n0.style.display = 'none';
			if(n1) n1.style.display = 'none';

			if(document.getElementById('squeeze'))
				document.getElementById('squeeze').style.margin = '0px';

			n2.style.margin = '0px';
			if(fn11_c58d3a71(n2.tagName, 'td')) n2.style.width = '100%';

			document.body.style.margin = '1px';
		}

		fn39_c58d3a71(window, 'scroll', fn07_c58d3a71);

		if(pf) return;
	}

	if(n0) n0.style.visibility = 'hidden';
	if(n1) n1.style.visibility = 'hidden';

	if(p1 == 'new' && n2)
	{
		try {

			fn28_c58d3a71(n2);
			fn33_c58d3a71(fn32_c58d3a71((n1 || n0), 'c58d3a78'));

		} catch (_err_) {;}
	}

	try {

		fn41_c58d3a71(fn32_c58d3a71((n1 || n0), 'c58d3a79'));

	} catch (_err_) {;}

	try {

		var vn = (p1 == 'new');
		fn01_c58d3a71(n0, 0, vn);
		fn01_c58d3a71(n1, 1, vn);

	} catch (_err_) {;}

	if(n0) n0.style.visibility = 'visible';
	if(n1) n1.style.visibility = 'visible';

	if(p1 == 'new')
	{
		try {

			var ki = p1 + (ap[2] || '') + (ap[3] || '') + (ap[4] || '');
			ki = escape(ki.toLowerCase());
			fn12_c58d3a71(n2, ki);

		} catch (_err_) {;}
	}

	if((p1 == 'a' || p1 == 'av' || p1 == 'author') && !ap[3] && ap[2] && n2)
	{
		try {

			if(n2 != document.getElementById('center'))
			{
				var a = n2.getElementsByTagName('h1'), f = 0;

				for(var i = 0; i < a.length; i++)
				{
					if(fn11_c58d3a71(a[i].className, 'title'))
						{ fn14_c58d3a71(n2, a[i]); f = 1; break; }
				}

				if(!f && fn11_c58d3a71(n2.tagName, 'td'))
				{
					var ms = n2.firstChild;

					while(ms && (ms = ms.nextSibling) != null)
					{
						if(fn11_c58d3a71(ms.tagName, 'h2'))
							fn14_c58d3a71(n2, ms);
					}
				}
			}
			else
			{
				var a = n2.getElementsByTagName('div');

				for(var i = 0; i < a.length; i++)
				{
					if(fn11_c58d3a71(a[i].className, 'clear-block'))
						{ fn14_c58d3a71(a[i], a[i].firstChild); break; }
				}
			}

		} catch (_err_) {;}
	}

	try {

		var ab = (n2 ? n2.getElementsByTagName('ul') : '');

		for(var ib = 0; ib < ab.length; ib++)
		{
			if(fn11_c58d3a71(ab[ib].className, 'pager'))
			{
				ab = ab[ib].getElementsByTagName('li');

				if((ib = ab.length - 2) < 0) break;

				if(fn11_c58d3a71(ab[1].className, 'pager-previous') &&
					ab[1].firstChild) pgp_c58d3a71 = ab[1].firstChild.href;

				if(fn11_c58d3a71(ab[ib].className, 'pager-next') &&
					ab[ib].firstChild) pgn_c58d3a71 = ab[ib].firstChild.href;

				break;
			}
		}

		if(pgp_c58d3a71 || pgn_c58d3a71)
			fn39_c58d3a71(document, 'keydown', fn15_c58d3a71);

	} catch (_err_) {;}

	if((document.getElementById('comments') ||
		document.getElementById('forum-comments'))
		&& document.getElementById('new'))
	{
		try {

			var aj = (document.getElementById('comments') ||
				document.getElementById('forum-comments'));

			aj = aj.getElementsByTagName('span');

			var aj2 = new Array(), ij2 = 0;

			for(var ij = 0; ij < aj.length; ij++)
			{
				if(fn11_c58d3a71(aj[ij].className, 'new'))
					aj2[ij2++] = aj[ij];
			}

			if(ij2 > 1)
			{
				ajn_c58d3a71 = aj2;

				for(var ij = 0; ij < ij2; ij++)
				{
					var nj = aj2[ij];
					nj.style.display = 'inline';
					nj.style.position = 'relative';

					if(ij != (ij2 - 1)) nj.innerHTML += '&nbsp;&#9660;';
					else nj.innerHTML += '&nbsp;&#9650;';

					fn18_c58d3a71(nj, 1);
					fn39_c58d3a71(nj, 'click', fn16_c58d3a71);
				}

			} else { if(ij2 == 1) fn18_c58d3a71(aj2[0], 0); }

		} catch (_err_) {;}
	}

	if(p1 == 'tracker' && document.getElementById('tracker'))
		try { fn10_c58d3a71(); } catch (_err_) {;}

	try {

		var a = document.body.getElementsByTagName('input');

		for(var i = 0; i < a.length; i++)
		{
			if(fn11_c58d3a71(a[i].name, 'ftpfile'))
				fn39_c58d3a71(a[i], 'blur', fn24_c58d3a71);

			if(fn11_c58d3a71(a[i].name, 'genre'))
				fn39_c58d3a71(a[i], 'blur', fn21_c58d3a71);
		}

	} catch (_err_) {;}

	try {

		if(fn05_c58d3a71(cfg_c58d3a71, 'hj') == '1')
		{
			if(p1.charAt(0) != 'b' || !ap[4]
				|| !fn11_c58d3a71(ap[3], 'join')) cfg_c58d3a71 =
			fn04_c58d3a71(cfg_c58d3a71, 'c58d3a71', 'hj', '0');

			if(p1.charAt(0) == 'b' && fn11_c58d3a71(ap[3], 'dojoin')
				&& ap[4] && n2 && history.length > 1)
			{
				var hl = n2.appendChild(document.createElement('a'));
				hl.href = 'javascript:history.go(-2)';
				hl.innerHTML = '(продолжить обработку)';
			}
		}

		if(p1.charAt(0) == 'a' && fn11_c58d3a71(ap[3], 'edit') && n2)
		{
			var a = n2.getElementsByTagName('input');

			for(var i = 0; i < a.length; i++)
			{
				if(a[i].id && a[i].id.substring(0, 4) == 'lang')
				{
					if(!fn11_c58d3a71(a[i].value, 'ru'))
						a[i].style.color = 'red';
					fn39_c58d3a71(a[i], 'change', fn13_c58d3a71);
				}
			}

			cfg_c58d3a71 = fn04_c58d3a71(cfg_c58d3a71, 'c58d3a71', 'hj', '1');
		}

	} catch (_err_) {;}

	try {

		var gf = document.getElementById('cse-search-box');

		if(gf)
		{
			var a = gf.getElementsByTagName('br');

			for(var i = 0; i < a.length; i++)
				{ a[i].style.display = 'none'; }

			gf.innerHTML += '<input type="hidden" name="safe" value="off" />'
			+ '<p><select id="c58d3ab0" name="as_sitesearch"><option value="">'
			+ '– искать везде</option><option value="lib.rus.ec/node/">'
			+ '– по форуму и блогам</option><option value="lib.rus.ec/b/*/read">'
			+ '– только по текстам книг</option><option value="lib.rus.ec/b/">'
			+ '– по текстам и описаниям книг</option><option value="lib.rus.ec/a/">'
			+ '– по страницам авторов</option></select></p>';

			var n = document.getElementById('c58d3ab0');
			n.selectedIndex = fn05_c58d3a71(cfg_c58d3a71, 'gf');
			fn39_c58d3a71(n, 'change', fn19_c58d3a71);
			n.style.padding = '0px';
		}

		if(p1 == 'booksearch') fn20_c58d3a71(n2);

	} catch (_err_) {;}

	fn00_ea29d0c6();
}

function fn01_c58d3a71(bar, ib, vn)
{
	//if (/MSIE (\d+\.\d+);/.test(navigator.userAgent)) //test for MSIE x.x;
	//var ieversion=new Number(RegExp.$1) // capture x.x portion and store as a number
	//if (ieversion==6) return;

	if(!bar || fn11_c58d3a71(bar.style.display, 'none')) return;

	bar.style.overflow = 'hidden';
	bar.style.wordWrap = 'break-word';

	var ct = (document.getElementById('center') != null);
	if(!ct) bar.style.paddingLeft = bar.style.paddingRight = '10px';

	var a = bar.getElementsByTagName('div'), ag = new Array(), ig = 0;
	var h0 = new Array(), h1 = new Array(), i1 = 0, hn = null;

	for(var i = 0; i < a.length; i++)
	{
		if(!fn29_c58d3a71(a[i])) continue;

		if(a[i].id == 'block-block-2' && a[i].innerHTML.length < 120)
		{ a[i].style.display = 'none'; continue; }

		var n = null;

		for(var s = 0; s < a[i].childNodes.length; s++)
		{
			var t = a[i].childNodes[s].tagName;

			if(!t || (!fn11_c58d3a71(t.substring(0, 1), 'h')
				&& !fn11_c58d3a71(t, 'div'))) continue;

			n = a[i].childNodes[s];
			break;
		}

		if(n && fn11_c58d3a71(n.className, 'blockinner'))
		{
			var nc = n;
			n = null;

			for(var s = 0; s < nc.childNodes.length; s++)
			{
				var t = nc.childNodes[s].tagName;

				if(!t || (!fn11_c58d3a71(t.substring(0, 1), 'h')
					&& !fn11_c58d3a71(t, 'div'))) continue;

				n = nc.childNodes[s];
				break;
			}
		}

		if(!n) continue;

		ag[ig] = a[i];
		h0[ig] = n;

		if(fn11_c58d3a71(n.className, 'content')) h1[i1++] = ig;
		else { if(!hn) hn = n; }

		ig++;
	}

	if(!ig || !hn) return;

	while(i1--)
	{
		var n = h0[h1[i1]];
		n = n.parentNode.insertBefore(hn.cloneNode(true), n);
		h0[h1[i1]] = n;

		if(fn11_c58d3a71(n.tagName, 'div') &&
			n.getElementsByTagName('h3').length)
		n = n.getElementsByTagName('h3')[0];

		n.innerHTML = (fn11_c58d3a71(ag[h1[i1]].id, 'c58d3a79') ? 'Рюкзачок'
		: ((vn && fn11_c58d3a71(ag[h1[i1]].id, 'c58d3a78')) ? 'Вид списка' : ''));
	}

	while(ig--)
	{
		var n = h0[ig];

		var fc = (fn11_c58d3a71(n.tagName, 'div') &&
			n.getElementsByTagName('h3').length);

		var nc = (fc ? n.getElementsByTagName('h3')[0] : n);

		if(!nc.innerHTML.length)
		{
			if(fn11_c58d3a71(ag[ig].id, 'block-librusec-booksearch'))
			{
				nc.innerHTML = 'Поиск книг';

				var sf = ag[ig].getElementsByTagName('form')[0];
				if(!sf['ask']) sf = sf.parentNode.appendChild(sf);

				if(sf && sf.length)
				{
					sf.innerHTML = sf.innerHTML.replace('Поиск книг:', '')
					.replace('><', '> <').replace('name=',
					' style="width:70%" name=') + '<div class="item-list">'
					+ '<ul style="margin-top:7px; font-size:90%"><li>'
					+ '<a href="/book">Расширенный поиск</a><li><a '
					+ 'href="/stat/b">Популярные книги</a></ul></div>'
//					+ '<li><a href="/searchhelp">Помогите найти!..</a></ul></div>';
				}

			} else if(fn11_c58d3a71(ag[ig].id, 'block-block-7'))
				nc.innerHTML = 'Поиск по сайту';
					else nc.innerHTML = '* * *';
		}

		if(!n.className) n.className = 'title';
		nc.style.textAlign = 'center';

		n.style.marginTop = ((fn11_c58d3a71(bar.tagName, 'td')
			&& !fc) ? '0px' : (ct ? '5px' : '-5px'));

		if(fn11_c58d3a71(ag[ig].id, 'block-user-3'))
		{
			var ae = ag[ig].getElementsByTagName('em'), uc;

			if(ae.length == 2 && !isNaN(uc = parseInt(ae[0].innerHTML)
				+ parseInt(ae[1].innerHTML))) ae[1].innerHTML +=
			' (Всего: ' + uc + ')';

			var ub = ag[ig].getElementsByTagName('ul')[0];

			if(ub && ub.getElementsByTagName('a').length)
			{
				var ed = document.createElement('input');

				ed.type = 'text';
				ed.maxLength = 110;
				ed.style.width = '96%';
				ed.style.border = 'solid 1px #AEAEAE';
				ed.style.backgroundColor = 'transparent';
				ed.style.opacity = '0.35';
				ed.style.filter = 'Alpha(opacity=35)';
				ed.autocomplete = 'off';
				ed.title = 'подсвечивать ники (a,b,c)';

				ed = ub.parentNode.appendChild(ed);
				fn25_c58d3a71(ed, 1);

				fn39_c58d3a71(ed, 'focus', fn27_c58d3a71);
				fn39_c58d3a71(ed, 'blur', fn27_c58d3a71);
				fn39_c58d3a71(ed, 'keydown', fn40_c58d3a71);
			}
		}

		if(fn11_c58d3a71(ag[ig].id, 'block-comment-0'))
		{
			if(nc.childNodes.length == 1) nc.innerHTML =
			'<a href=/tracker>' + nc.innerHTML + '</a>';

			if((document.getElementById('comments') ||
				document.getElementById('forum-comments'))
				&& document.getElementById('new'))
			{
				nc.innerHTML += '<br /><a style="font-size:60%" href="#new">'
				+ '(<span style="color:#F01200">новые на '
				+ 'странице</span>)</a>';
			}
		}

		if(fn11_c58d3a71(ag[ig].id, 'block-privatemsg-privatemsg-menu'))
		{
			if(nc.innerHTML.indexOf('riv') >= 0) nc.innerHTML = 'Личка';

			var am = ag[ig].getElementsByTagName('a'), em = null;

			for(var im = 0; im < am.length; im++)
			{
				var sm = (am[im].href || '').toLowerCase().split('/');

				if(sm[3] == 'messages' && (sm[4] == 'inbox' || !sm[4]))
				{ em = am[im].parentNode; break; }
			}

			if(em && em.innerHTML.indexOf('(') >= 0 &&
				em.innerHTML.indexOf(')') >= 0) nc.style.color = '#F01200';
		}

		if(nc.firstChild && nc.firstChild.href)
			nc.firstChild.style.fontSize = '100%';

		n.innerHTML = '<span style="float:' + (ib ? 'right;' :'left;')
		+ 'position:relative; cursor:pointer; color:#A7A7A7; display:inline;'
		+ 'font:normal normal normal 9px/10px \'Courier New\','
		+ '\'Lucida Console\',\'BatangChe\',monospace; padding:0px;'
		+ 'margin:-4px; margin-' + (ib ? 'left:' :'right:') + '-11px;" '
		+ 'title="&#8597;" onmouseover="this.style.color=\'#585858\'" '
		+ 'onmouseout="this.style.color=\'#A7A7A7\'">[-]</span>'
		+ n.innerHTML;

		nc.unselectable = n.firstChild.unselectable = 'on';
		n.style.cursor = 'default';

		if(n.addEventListener)
		{
			n.firstChild.addEventListener('click', function(ev) {
			fn02_c58d3a71(ev, this, 0, 0); }, false);

			n.addEventListener('dblclick', function(ev) {
			if(!window.opera && window.getSelection)
				window.getSelection().collapse(document.body, 0);
			fn02_c58d3a71(ev, this.firstChild, 0, 0); }, false);
		}
		else
		{
			n.firstChild.attachEvent('onclick', function() {
			fn02_c58d3a71(event, event.srcElement, 0, 0); } );

			n.attachEvent('ondblclick', function() {
			fn02_c58d3a71(event, event.srcElement.firstChild, 0, 0); } );
		}

		var sc = 0, sp = (ag[ig].id || ag[ig].className || '')
		+ (n.textContent || n.innerText || '').substring(3, 23);

		for(var si = 0; si < sp.length; si++) { sc += sp.charCodeAt(si); }

		n.firstChild.id = '' + (sc % 100000) + '_c58d3a71';

		if(cfg_c58d3a71) fn02_c58d3a71(null, n.firstChild, 0, 0);
	}
}

function fn02_c58d3a71(ev, p, af, ad)
{
	var r, n = null;

	if(!p || (r = p.parentNode) == null || (r = r.parentNode) == null) return;

	for(var i = 0; i < r.childNodes.length; i++)
	{
		if(fn11_c58d3a71(r.childNodes[i].className, 'content'))
		{
			n = r.childNodes[i];
			break;
		}
	}

	if(!n) return;

	var g = p.id.split('_')[0];

	if(!ev)
	{
		if((r = fn05_c58d3a71(cfg_c58d3a71, g)) != null)
			fn06_c58d3a71(p, n, (r == '1'));

		return;
	}

	var sd = (af ? ad : fn11_c58d3a71(n.style.display, 'none'));

	fn06_c58d3a71(p, n, sd);
	cfg_c58d3a71 = fn04_c58d3a71(cfg_c58d3a71, 'c58d3a71', g, sd ? 1 : 0);

	if(!af && ev && ev.shiftKey && (r = r.parentNode) != null
		&& (r = r.parentNode) != null)
	{
		var aa = r.getElementsByTagName('span');

		for(var ia = 0; ia < aa.length; ia++)
		{
			if(aa[ia].id && aa[ia] != p && (aa[ia].id.split('_'))[1]
				== 'c58d3a71') fn02_c58d3a71(ev, aa[ia], 1, sd);
		}
	}
}

function fn03_c58d3a71(s, m)
{
	var c = document.cookie, i;
	if(!c || (i = c.indexOf(s)) < 0) return null;

	i += s.length;
	c = (c.substring(i + ((c.charAt(i) == '=') ? 1 : 0))).split(';')[0];
	if(m && c.length > m) c = c.substring(m / 4);

	return c;
}

function fn04_c58d3a71(b, s, ki, kv)
{
	var r = ki + '(' + kv + ')';

	if(!ki || !ki.length || (b && b.indexOf(r) >= 0)) return b;

	if(!b) b = '';

	if(b.indexOf(ki + '(') >= 0)
		r = b.replace(new RegExp(ki + '[\(][^\)]*[\)]'), r);
	else r = b + r;

	document.cookie = s + '=' + r
	+ '; path=/; expires=Mon, 31 Dec 2040 23:59:59 GMT';

	return r;
}

function fn05_c58d3a71(c, i)
{
	var v;

	if(!c || !i || !i.length || (v = c.indexOf(i + '(')) < 0
		|| (v = c.substring(v + i.length + 1)) == '')
	return null;

	return v.split(')')[0];
}

function fn06_c58d3a71(n0, n1, f)
{
	n1.style.display =  (f ? 'block' : 'none');
	n0.innerHTML = (f ? '[-]' : '[+]');
}

function fn07_c58d3a71()
{
	try {

		sp0_c58d3a71 = document.body.scrollTop || window.pageYOffset ||
		(document.body.parentNode ? document.body.parentNode.scrollTop : 0);

		if(sp0_c58d3a71 > 80)
		{
			clearTimeout(stm_c58d3a71);
			stm_c58d3a71 = setTimeout(fn08_c58d3a71, 400);
		}

	} catch (_err_) {;}
}

function fn08_c58d3a71()
{
	try {

		if(Math.abs(sp0_c58d3a71 - sp1_c58d3a71) > 80)
		{
			if((sp1_c58d3a71 = sp0_c58d3a71) > 80) bmk_c58d3a71 =
			fn04_c58d3a71(bmk_c58d3a71, 'c58d3a72', idb_c58d3a71,
			(Math.floor(100 / ((document.body.scrollHeight + 1) /
			(sp1_c58d3a71 + 1)) * 10000)) );
		}

	} catch (_err_) {;}
}

function fn09_c58d3a71(sp, nm)
{
	var n = (nm.getElementsByTagName('h1')[0]
		|| nm.getElementsByTagName('h2')[0]);

	if(!n) return;

	n.innerHTML = '<span style="position:relative; float:right;'
	+ 'cursor:pointer; font-size:10px; margin-top:6px; line-height:15px" '
	+ 'onclick="window.scrollTo(0, document.body.scrollHeight * ('
	+ sp + ' / 10000 / 100))">ЗАКЛАДКА</span>' + n.innerHTML;

	fn17_c58d3a71(n.firstChild);
}

function fn10_c58d3a71(sp, d)
{
	fn30_c58d3a71('table.sticky-header', 'opacity:0.7');

	var t0 = document.getElementById('tracker');
	t0 = t0.getElementsByTagName('table');

	for(var i = 0; i < t0.length; i++)
	{
		if(!t0[i].className || t0[i].className.substring(0,
			6).toLowerCase() != 'sticky') continue;

		var t1 = t0[i].getElementsByTagName('thead')[0];
		if(t1) t1 = t1.getElementsByTagName('tr')[0];
		if(t1) t1 = t1.getElementsByTagName('th');

		for(var i1 = 0; t1 && i1 < t1.length; i1++)
		{
			if(t1[i1].innerHTML.charAt(9) == ' ')
			{
				t1[i1].innerHTML = 'Обновлено';
				break;
			}
		}
	}
}

function fn11_c58d3a71(s0, s1)
{
	if(!s0 || s0 == '') return false;
	return (s0.toLowerCase() == s1);
}

function fn12_c58d3a71(n, ki)
{
	if(!n) return;

	var bm = fn03_c58d3a71('c58d3a73', 100);
	var kv = fn05_c58d3a71(bm, ki);

	var a = n.getElementsByTagName('a');
	var f0 = 0, f1 = 0;

	if(!kv) { kv = '0+0'; f0 = f1 = 1; }
	kv = kv.split('+');

	kv[0] = parseInt(kv[0]);
	if(isNaN(kv[0])) kv[0] = 0;
	kv[1] = parseInt(kv[1]);
	if(isNaN(kv[1])) kv[1] = 0;

	for(var i = 0; i < a.length; i++)
	{
		if(!a[i].href) continue;

		var u = a[i].href.split('/');

		if(!u[5] && (u[3] == 'b' || u[3] == 'B') && u[4])
		{
			if(fn11_c58d3a71(a[i].parentNode.tagName, 'p') ||
				fn11_c58d3a71(a[i].style.display, 'none')) continue;

			var b = parseInt(u[4]);
			if(isNaN(b)) continue;

			if(b >= kv[0]) { if(!f0) { kv[1] = kv[0]; f0 = 1; } kv[0] = b; }

			if(!f1 && b <= kv[1])
			{
				fn17_c58d3a71(a[i]);
				f1 = 1;
			}
		}
	}

	fn04_c58d3a71(bm, 'c58d3a73', ki, '' + kv[0] + '+' + kv[1]);
}

function fn13_c58d3a71(ev)
{
	if(!ev) ev = window.event;
	var n = (ev.srcElement || ev.target);

	if(fn11_c58d3a71(n.value, 'ru')) n.style.color = 'black';
	else n.style.color = 'red';
}

function fn14_c58d3a71(mn, h)
{
	if(!mn || !h) return;

	var n = h, d0 = null, d1 = null;

	while(n && (n = n.nextSibling) != null)
	{
		if(!n.tagName) continue;
		var t = n.tagName.toLowerCase();

		if(fn11_c58d3a71(n.style.overflow, 'auto')) break;
		if(!d0 && (t == 'p' || t == 'img')) d0 = n;

		if(t == 'p' && n.firstChild && n.firstChild.href)
		{
			var u = n.firstChild.href.split('/');
			var f = ((u.length > 5) ? u[5].toLowerCase() : '');

			if(f == 'edit' || f == 'addbook') { d1 = n; break; }
		}

		if(t == 'form' || t == 'input' || t == 'select') break;
	}

	n = d0 || h;

	if(d1 && n && n != d1)
	{
		var np = mn.insertBefore(document.createElement('div'), n);
		if(!np) return;

		var s = np.style;
		s.maxHeight = '400px';
		s.overflow = 'auto';
		s.scrollbarDarkShadowColor = 'scrollbar';
		s.wordWrap = 'break-word';

		while(n && n != d1)
		{
			var nx = n;
			n = n.nextSibling;
			np.appendChild(nx);
		}

		var hx = mn.insertBefore(document.createElement('div'), np);

		hx.innerHTML = 'Описание автора';

		hx.style.width = '100%';
		hx.style.fontSize = '130%';

		var bx = fn22_c58d3a71(hx, 0);
		bx.style.color = '#585858';
		bx.style.marginTop = '2px';

		if(bx.addEventListener) { bx.addEventListener('click',
			function(){ fn23_c58d3a71(this); }, false);
		} else bx.attachEvent('onclick',
			function(){ fn23_c58d3a71(event.srcElement); });

		if(fn05_c58d3a71(cfg_c58d3a71, 'avd') == '0') fn23_c58d3a71(bx);
	}
}

function fn15_c58d3a71(ev)
{
	try {

		if(!ev) ev = window.event;

		if(ev && ev.ctrlKey && !(ev.srcElement || ev.target || this).value)
		{
			if(ev.keyCode == 37 && pgp_c58d3a71)
				window.location = unescape(pgp_c58d3a71);

			if(ev.keyCode == 39 && pgn_c58d3a71)
				window.location = unescape(pgn_c58d3a71);
		}

	} catch (_err_) {;}
}

function fn16_c58d3a71()
{
	var n = ((this != window) ? this :
		(this.event ? this.event.srcElement : null));
	var a = ajn_c58d3a71;

	if(!n || !a) return;

	try {

		for(var i = 0; i < a.length; i++)
		{
			if(a[i] == n)
			{
				if(i != (a.length - 1)) a[i + 1].scrollIntoView();
				else a[0].scrollIntoView();

				break;
			}
		}

	} catch (_err_) {;}
}

function fn17_c58d3a71(n)
{
	n.style.backgroundRepeat = 'repeat';
	n.style.backgroundImage = 'url("data:image/gif;base64,'
	+ 'R0lGODlhDwAPABEAACH5BAEAAAAALAAAAAAPAA8AoQAAAP+/v/+urgA'
	+ 'AAAIiBGR4yWEOoIyv0mvndbrvbIEf5Y2idoLltIaj11LKzCxAAQA7")';
	n.style.backgroundColor = '#FFDFDF';
	n.style.paddingLeft = n.style.paddingRight = '1px';
}

function fn18_c58d3a71(n, f)
{
	n.style.color = '#F01200';
	n.style.cursor = (f ? 'pointer' : 'default');
	n.unselectable = 'on';

	if(fn11_c58d3a71(n.parentNode.tagName, 'a') &&
		n.parentNode.parentNode.parentNode.appendChild(n) != null)
	{
		n.style.cssFloat = n.style.styleFloat = 'right';
		n.style.paddingLeft = n.style.paddingRight = '5px';
	}
}

function fn19_c58d3a71()
{
	var n = ((this != window) ? this :
		(this.event ? this.event.srcElement : null));

	cfg_c58d3a71 = fn04_c58d3a71(cfg_c58d3a71,
		'c58d3a71', 'gf', n.selectedIndex);
}

function fn20_c58d3a71(n)
{
	if(!n || !window.external || !("AddSearchProvider" in window.external)
		|| !(n = n.appendChild(document.createElement('div')))) return;

	n.innerHTML = '<i style="font-size:90%">Вы можете '
	+ '<a href="/opensearch.xml" onclick="window.external.'
	+ 'AddSearchProvider(this.href); return false;">добавить</a> '
	+ 'поиск книг в меню панели поиска вашего браузера.</i>';
}

function fn21_c58d3a71()
{
	var n = ((this != window) ? this :
		(this.event ? this.event.srcElement : null));

	if(n && n.value) n.value = n.value.replace(/ /g, '');
}

function fn22_c58d3a71(h, i)
{
	h.innerHTML = '<span style="float:right; position:relative;'
	+ 'cursor:pointer; display:inline; font:normal normal normal '
	+ '12px/13px \'Courier New\',\'Lucida Console\',\'BatangChe\','
	+ 'monospace; margin:1px; margin-right:22px" unselectable="on" '
	+ 'title="&#8597;" id="' + i + '_c58d3a74">[-]</span>' + h.innerHTML;

	h.style.backgroundColor = '#F7F8F9';

	return h.firstChild;
}

function fn23_c58d3a71(b)
{
	try {

		var mn = b.parentNode.nextSibling;
		var f = (fn11_c58d3a71(mn.style.display, 'none') ? 1 : 0);
		fn06_c58d3a71(b, mn, f);
		cfg_c58d3a71 = fn04_c58d3a71(cfg_c58d3a71, 'c58d3a71', 'avd', f);

	} catch (_err_) {;}
}

function fn24_c58d3a71()
{
	var n = ((this != window) ? this :
		(this.event ? this.event.srcElement : null));

	if(!n || !n.value) return;

	var s = n.value;

	while(s.charAt(s.length - 1) == ' ') { s = s.substring(0, s.length - 1); }
	while(s.charAt(0) == ' ') { s = s.substring(1); }

	if(!s.indexOf('ftp://'))
	{
		s = s.substring(6);

		n.value = s.substring(s.indexOf('/') +
			((s.split('/').length > 2) ? 0 : 1));
	}
}

function fn25_c58d3a71(ed, f)
{
	if(!ed || !ed.parentNode) return;

	var s = (f ? fn03_c58d3a71('c58d3a76', 661) : ed.value);
	if(s == null) s = '';

	if(f) ed.value = s = unescape(s);
	else s = s.replace(new RegExp('http://[^,]*/user/', 'ig'), ',#');

	var sa = s.split(','), i, j;

	if(!f) ed.value = fn38_c58d3a71(sa);

	var a = ed.parentNode.getElementsByTagName('a');

	for(i = 0; i < a.length; i++)
	{
		if(!f) a[i].style.color = '';

		for(j = 0; j < sa.length; j++)
		{
			if(a[i].innerHTML == sa[j] || (sa[j].charAt(0) == '#' &&
				a[i].href && a[i].href.split('/')[4] == sa[j].substring(1)))
			{ a[i].style.color = 'red'; break; }
		}
	}

	if(!f)
	{
		for(i = 0; i < sa.length; i++) { sa[i] = escape(sa[i]); }
		fn26_c58d3a71('c58d3a76', sa.join(','));
	}
}

function fn26_c58d3a71(i, s)
{
	if(s == null || s == fn03_c58d3a71(i)) return false;

	document.cookie = i + '=' + s
	+ '; path=/; expires=Mon, 31 Dec 2040 23:59:59 GMT';

	return true;
}

function fn27_c58d3a71(ev)
{
	var n = ((this != window) ? this :
		(this.event ? this.event.srcElement : null));

	if(!n) return;

	var s = n.style, f = ((ev || window.event).type.toLowerCase() == 'focus');

	s.backgroundColor = (f ? '' : 'transparent');
	s.opacity = (f ? '1.0' : '0.35');
	s.filter = (f ? 'Alpha()' : 'Alpha(opacity=35)');

	if(!f) fn25_c58d3a71(n, 0);
	else { if(n.value) n.value += ','; }
}

function fn28_c58d3a71(mn)
{
	if(!mn) return;

	var a0 = mn.getElementsByTagName('p');
	var g0 = new Array(), g1 = new Array(), i, j = 0, n0, n1, k;

	for(i = 0; i < a0.length; i++)
	{
		if(!fn11_c58d3a71(a0[i].className, 'genre')) continue;

		var a1 = a0[i].getElementsByTagName('a'), s = '';

		for(k = 0; k < a1.length; k++)
		{
			n1 = (a1[k].href || '').toLowerCase().split('/');

			if(n1[3] == 'g' && n1[4])
				s += 'g0-' + n1[4].replace(/_/, ' g1-') + ' ';
		}

		g0[j] = a0[i];
		g1[j++] = s;
	}

	var dc = (mn.currentStyle ? mn.currentStyle.backgroundColor :
	(window.getComputedStyle ? window.getComputedStyle(mn,
	 null).backgroundColor : '#FDFEFF'));

	for(i = 0; i < g0.length; i++)
	{
		n0 = g0[i]; n1 = g0[i + 1];
		var mx = document.createElement('div'), f = 0;
		mn = mx = n0.parentNode.insertBefore(mx, n0);
		mx.className = g1[i];

		var gc = document.createElement('span');
		gc.className = 'c58d3a88';
		mx.appendChild(gc);

		do {

			if(!n1 && ((fn11_c58d3a71(n0.tagName, 'br') && n0.nextSibling
				&& fn11_c58d3a71(n0.nextSibling.type, 'submit')) ||
				fn11_c58d3a71(n0.type, 'submit'))) break;

			if(!f && fn11_c58d3a71(n0.tagName, 'img') &&
				n0.src.indexOf('/znak') >= 0) { mn = mx; f = 1; }

			if(!f && fn11_c58d3a71(n0.type, 'checkbox') &&
				!isNaN(parseInt(n0.name))) { mn = mx; f = 1; }

			if(!f && fn11_c58d3a71(n0.tagName, 'h4')
				&& n0.innerHTML.indexOf('.20') > 1)
			{ mn = mx; f = 1; n0.style.backgroundColor = dc; }

			if(f && fn11_c58d3a71(n0.tagName, 'p'))
			{
				mn = mn.appendChild(document.createElement('div'));
				mn.className = 'c58d3a77';
				mn.style.scrollbarDarkShadowColor = 'scrollbar';
				mn.style.wordWrap = 'break-word';
				f = 0;
			}

			var nx = n0;
			n0 = n0.nextSibling;
			mn.appendChild(nx);

		} while(n0 && n0 != n1)

		n0 = g0[i].nextSibling;
		gc.appendChild(g0[i]);
		if(n0 && fn11_c58d3a71(n0.tagName, 'br')) gc.appendChild(n0);
	}
}

function fn29_c58d3a71(n)
{
	if(!n || !n.className) return false;
	var s = n.className.substring(0, 6).toLowerCase();
	return (s == 'block ' || s == 'block-' || s == 'clear-');
}

function fn30_c58d3a71(rn, rv)
{
	var s = document.styleSheets, i = s.length;

	if(i && s[0].insertRule && s[0].cssRules)
	{
		while(i--) { s[i].insertRule(rn + '{ ' + rv + '; }',
		s[i].cssRules.length); }
		return;
	}

	if(i && s[0].addRule)
	{
		rn = rn.split(',');
		while(i--) { for(var j = 0; j < rn.length; j++)
		{ s[i].addRule(rn[j], rv); } }
		return;
	}
}

function fn31_c58d3a71(s, f)
{
	var a = new Array('det_action', 'detective', 'det_irony', 'det_history',
	'det_classic', 'det_crime', 'det_hard', 'det_maniac', 'det_political',
	'det_police', 'thriller', 'det_espionage', 'det', 'children',
	'child_education', 'child_prose', 'child_sf', 'child_det', 'child_adv',
	'child_verse', 'child_tale', 'child', 'nonf_biography', 'nonfiction',
	'design', 'nonf_criticism', 'nonf_publicism', 'nonf', 'home_pets', 'home',
	'home_health', 'home_cooking', 'home_entertain', 'home_garden',
	'home_diy', 'home_sport', 'home_crafts', 'home_sex', 'comp_db',
	'comp_www', 'comp_hard', 'computers', 'comp_osnet', 'comp_programming',
	'comp_soft', 'comp_dsp', 'comp', 'love_history', 'love_short', 'love',
	'love_detective', 'love_contemporary', 'love_erotica', 'sci_anachem',
	'sci_cosmos', 'sci_biology', 'sci_biophys', 'sci_biochem', 'sci_geo',
	'sci_state', 'sci_business', 'sci_history', 'sci_culture', 'sci_math',
	'sci_medicine', 'science', 'sci_orgchem', 'sci_politics',
	'sci_psychology', 'sci_religion', 'sci_tech', 'sci_phys', 'sci_physchem',
	'sci_philosophy', 'sci_chem', 'sci_economy', 'sci_juris',
	'sci_linguistic', 'sci', 'dramaturgy', 'poetry', 'adv_western',
	'adv_history', 'adv_maritime', 'adventure', 'adv_indian', 'adv_animal',
	'adv_geo', 'adv', 'prose_history', 'prose_classic', 'prose_counter',
	'prose_military', 'prose', 'prose_rus_classic', 'prose_su_classics',
	'prose_contemporary', 'other', 'notes', 'religion_budda', 'religion',
	'religion_rel', 'religion_self', 'religion_esoterics', 'ref_guide',
	'ref_dict', 'reference', 'ref_ref', 'ref_encyc', 'ref', 'antique_ant',
	'antique_east', 'antique_russian', 'antique_european', 'antique_myths',
	'antique', 'sci_metal', 'sci_radio', 'sci_build', 'sci_transport',
	'sf_history', 'sf_action', 'sf_heroic', 'sf_fantasy_city', 'sf_detective',
	'sf_cyberpunk', 'sf_space', 'sf', 'sf_postapocalyptic', 'sf_social',
	'sf_horror', 'sf_fantasy', 'sf_epic', 'sf_humor', 'humor_anecdote',
	'humor', 'humor_prose', 'humor_verse', 'banking', 'accounting',
	'global_economy', 'paper_work', 'org_behavior', 'personal_finance',
	'small_business', 'marketing', 'real_estate', 'popular_business',
	'industries', 'job_hunting', 'economics_ref', 'management', 'stock',
	'economics', 'love_sf', 'sci_medicine_alternative', 'sci_philology');

	var r = '', i, j;
	s = s.split(',');

	if(f)
	{
		var d = new Array(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

		for(i = 0; i < s.length; i++)
		{
			for(j = 0; j < a.length; j++)
			{
				if(s[i] == a[j])
				{
					d[0 | (j / 16)] |= 1 << (j % 16);
					break;
				}
			}
		}

		r = d.join(',');
	}
	else
	{
		var p = 0, d, c = 0;

		for(i = 0; i < s.length; i++)
		{
			if(isNaN(d = parseInt(s[i]))) break;

			for(j = 1; j <= d; j *= 2)
			{
				if((d & j) && a[c]) r += (r ? ',' : '') + a[c];
				c++;
			}

			p += 16; c = p;
		}
	}

	delete a;
	return r;
}

function fn32_c58d3a71(bar, nid)
{
	if(!bar) return null;

	var a = bar.getElementsByTagName('div'), n = null, c;

	for(var i = 0; i < a.length; i++)
	{ if(fn29_c58d3a71(a[i])) { n = a[i]; break; } }

	if(!n) return null;

	if(window.opera && a[a.length - 1].id == 'footer')
	{
		document.body.appendChild(a[a.length - 1]);
		bar.innerHTML = bar.innerHTML;
	}

	c = bar.appendChild(n.cloneNode(false));
	c.id = nid;
	a = n.getElementsByTagName('div');

	if(fn11_c58d3a71(a[0].className, 'blockinner'))
	{
		c = c.appendChild(a[0].cloneNode(false));
		a = a[0].getElementsByTagName('div');
	}

	n = null;

	for(var i = 0; i < a.length; i++)
	{ if(fn11_c58d3a71(a[i].className, 'content')) { n = a[i]; break; } }

	return (n ? c.appendChild(n.cloneNode(false)) : null);
}

function fn33_c58d3a71(vt)
{
	if(!vt) return;

	vt.innerHTML = '<p style="margin:0px; margin-bottom:4px">Подсветка '
	+ '(<a href="/g" id="c58d3a80">id жанров</a>, через запятую):</p>'
	+ '<input type="text" id="c58d3a81" maxlength=1700 style="width:95%;'
	+ 'margin-bottom:10px" title="comp,sci_math,sf_horror, ..." /><br />'
	+ '<span style="line-height:21px">Цвет подсветки (<a href="http://'
	+ 'html-color-codes.info/" target="_blank">HTML</a>): </span><input '
	+ 'type="text" id="c58d3a83" maxlength=7 style="width:70px; text-align:'
	+ 'center" value="#EEF2F9" /><p style="margin:0px; margin-top:10px">'
	+ '<span style="line-height:21px">Макс. высота аннотации: </span><input '
	+ 'type="text" id="c58d3a82" maxlength=4 style="width:37px; text-align:'
	+ 'center" value="96" title="0 = не ограничивать" /> px.</p>'
	+ '<div style="margin-top:7px"><input type="checkbox" id="c58d3a84" '
	+ 'style="margin:0px; padding:1px" /><label for="c58d3a84"> Убрать '
	+ 'названия жанров</label><br /><input type="checkbox" id="c58d3a85" '
	+ 'style="margin:0px; padding:1px" /><label for="c58d3a85"> Убрать '
	+ 'картинки</label></div>';

	for(var i = 1; i < 6; i++)
	{
		var b = document.getElementById('c58d3a8' + i);
		fn39_c58d3a71(b, ((i < 4) ? 'blur' : 'click'), fn34_c58d3a71);
		if(i < 4) fn39_c58d3a71(b, 'keydown', fn40_c58d3a71);
	}

	fn36_c58d3a71(null);
	fn37_c58d3a71(null);
	fn35_c58d3a71(null);
}

function fn34_c58d3a71()
{
	var n = ((this != window) ? this :
		(this.event ? this.event.srcElement : null));

	if(!n) return;

	if(n.id == 'c58d3a81' || n.id == 'c58d3a83') fn36_c58d3a71(n);
	else { if(n.id == 'c58d3a82') fn35_c58d3a71(n);
		else fn37_c58d3a71(n);
	}
}

function fn35_c58d3a71(n)
{
	var mh;

	if(n)
	{
		mh = parseInt(n.value);
		if(isNaN(mh)) n.value = mh = 96;
		if(mh < 32) n.value = mh = 0;
		cfg_c58d3a71 = fn04_c58d3a71(cfg_c58d3a71, 'c58d3a71', 'amh', mh);
		if(mh == 0) mh = 32767;
	}
	else
	{
		mh = fn05_c58d3a71(cfg_c58d3a71, 'amh');
		if(mh == null) mh = 96;
		document.getElementById('c58d3a82').value = mh;
		if(mh == 0) return;
	}

	fn30_c58d3a71('.c58d3a77', 'max-height:' + mh
	+ 'px; overflow:auto; margin-bottom:5px');
}

function fn36_c58d3a71(n)
{
	var v, s = '', f = 0;

	if(n)
	{
		if(n.id == 'c58d3a83')
		{
			v = (n.value || '').toUpperCase().split('');

			if(v[0] == '#') v.splice(0, 1);
			if(v.length != 6 || !v.length) v = ('EEF2F9').split('');

			for(var i = 0; i < v.length; i++)
			{
				s = v[i].charCodeAt(0);

				if(s < 48 || s > 70 || (s > 57 && s < 65))
				{ v = ('EEF2F9').split(''); break }
			}

			n.value = '#' + (v = v.join(''));

			if((f = fn05_c58d3a71(cfg_c58d3a71, 'hcl')) != v) cfg_c58d3a71 =
				fn04_c58d3a71(cfg_c58d3a71, 'c58d3a71', 'hcl', v);

			f = (f != v && cfg_c58d3a71 && (f || v != 'EEF2F9'));
		}
		else
		{
			v = (n.value || '').split(',');
			v = n.value = fn38_c58d3a71(v);
			f = fn26_c58d3a71('c58d3a86', fn31_c58d3a71(v, 1));
		}

		if(f && confirm('Обновить страницу?'))
			location.reload(false);
	}
	else
	{
		if((v = fn03_c58d3a71('c58d3a86')) != null) v = fn31_c58d3a71(v, 0);

		f = '#' + (fn05_c58d3a71(cfg_c58d3a71, 'hcl') || 'EEF2F9');
		document.getElementById('c58d3a83').value = f;

		if(!v) return;

		document.getElementById('c58d3a81').value = v;

		v = v.split(',');

		for(var i = 0; i < v.length; i++)
		{ s += (s ? ', ' : '') + '.g0-' + v[i].replace(/_/, '.g1-'); }

		fn30_c58d3a71(s, 'background-color:' + f);
	}
}

function fn37_c58d3a71(n)
{
	var v1 = '', v2 = '';

	if(n)
	{
		var v = (n.checked ? '1' : '0'), i = 'hgl';

		if(n.id == 'c58d3a84') v1 = v;
		else { v2 = v; i = 'hai'; }

		cfg_c58d3a71 = fn04_c58d3a71(cfg_c58d3a71, 'c58d3a71', i, v);
	}
	else
	{
		if((v1 = fn05_c58d3a71(cfg_c58d3a71, 'hgl')) == '1')
			document.getElementById('c58d3a84').checked = true;

		if((v2 = fn05_c58d3a71(cfg_c58d3a71, 'hai')) == '1')
			document.getElementById('c58d3a85').checked = true;
	}

	if(v1) fn30_c58d3a71('.c58d3a88', 'display:'
		+ ((v1 != '0') ? 'none' : 'inline'));

	if(v2) fn30_c58d3a71('.c58d3a77 img', 'display:'
		+ ((v2 != '0') ? 'none' : 'inline'));
}

function fn38_c58d3a71(sa)
{
	for(var i = 0; i < sa.length; i++)
	{
		while(sa[i].charAt(sa[i].length - 1) == ' ')
			{ sa[i] = sa[i].substring(0, sa[i].length - 1); }
		while(sa[i].charAt(0) == ' ') { sa[i] = sa[i].substring(1); }
	}

	for(var i = 0; i < sa.length; i++)
	{
		while(sa[i] == '') { sa.splice(i, 1); }

		for(var j = (i + 1); j < sa.length; j++)
			{ while(sa[i] == sa[j]) sa.splice(j, 1); }
	}

	return sa.join(',');
}

function fn39_c58d3a71(o, s, f)
{
	if(!o) return;

	if(o.addEventListener) o.addEventListener(s, f, false);
	else o.attachEvent(('on' + s), f);
}

function fn40_c58d3a71(ev)
{
	try {

		if(!ev) ev = window.event;
		if(ev.keyCode == 13) ((this != window) ? this : ev.srcElement).blur();

	} catch (_err_) {;}
}

function fn41_c58d3a71(vt)
{
	if(!vt) return;

	vt.innerHTML = '<input type="checkbox" id="c58d3a90" style="margin:0px;'
	+ 'padding:1px" /><label for="c58d3a90"> Перехватывать закачки</label>'
	+ '<p style="margin:0px; margin-top:8px; margin-bottom:7px">'
	+ '<input type="button" id="c58d3a91" disabled style="width:75px;'
	+ 'margin-bottom:4px" value="Список" title="список для качалки" /> '
	+ '<input type="button" id="c58d3a92" disabled style="width:75px;'
	+ 'margin-bottom:4px" value="Скачать" title="все книги одним архивом" /> '
	+ '<input type="button" disabled id="c58d3a93" style="width:75px;'
	+ 'margin-bottom:4px" value="Очистить" title="удалить все" /></p>'
	+ '<div id="c58d3a99" style="height:98px; width:97%; overflow:auto;'
	+ 'padding-left:1px; border:inset 1px #AEAEAE; font:normal normal normal '
	+ '11px/14px \'Courier New\',\'Lucida Console\',\'BatangChe\',monospace">'
	+ '</div><p style="margin:0px; margin-top:5px; margin-bottom:5px">'
	+ 'Всего книг: <b id="c58d3a96">0</b>. Добавить:</p><div style="width:'
	+ '98%; overflow:hidden"><input type="text" id="c58d3a94" maxlength=256 '
	+ 'style="width:100%" title="url или id книги (-id или -url чтобы '
	+ 'удалить)" /></div><p style="margin:0px; margin-top:5px">'
	+ '<a id="c58d3a95" href="#selected">(добавить все выбранное)</a></p>'
	+ '<p id="c58d3a98" style="margin:0px; margin-top:4px">Выкачивать: '
	+ '<select id="c58d3a89" style="min-width:50px"></select></p>';

	if(document.getElementById('user-login-form'))
	{
		document.getElementById('c58d3a92').style.display = 'none';
		document.getElementById('c58d3a95').style.display = 'none';
		document.getElementById('c58d3a98').style.display = 'none';
	}

	bpd_c58d3a71.a = new Array();

	if(fn05_c58d3a71(cfg_c58d3a71, 'dch') == '1') fn50_c58d3a71(1);

	for(var i = 0; i < 6; i++)
	{
		var b = document.getElementById('c58d3a9' + i);
		fn39_c58d3a71(b, ((i != 4) ? 'click' : 'blur'), fn42_c58d3a71);
		if(i == 4) fn39_c58d3a71(b, 'keydown', fn40_c58d3a71);
	}

	fn30_c58d3a71('#c58d3a99 a', 'text-decoration:none; font-weight:normal;'
	+ 'border:none; padding-left:1px');
	fn30_c58d3a71('#c58d3a99 a:hover', 'background-color:#C7F5C0');

	fn46_c58d3a71();

	var s = document.getElementById('c58d3a89'), o, v;

	if((o = document.getElementById('useropt')) != null)
	{
		v = new Array('0', 'fb2', 'html', 'txt');

		for(var i = 0; i < o.options.length; i++)
		{
			v[i + 1] = escape(o.options[i].value || o.options[i].innerHTML);
			if(o.options[i].selected) v[0] = i;
		}

		fn26_c58d3a71('c58d3a87', v.join(','));
		fn39_c58d3a71(o, 'change', fn51_c58d3a71);

	} else v = (fn03_c58d3a71('c58d3a87') || '0,fb2,html,txt').split(',');

	for(var i = 1; i < v.length; i++)
	{
		o = s.appendChild(document.createElement('option'));
		o.value = o.innerHTML = unescape(v[i]);
		if((i - 1) == v[0]) o.selected = true;
	}

	fn39_c58d3a71(s, 'change', fn51_c58d3a71);
	fn39_c58d3a71(window, 'focus', fn46_c58d3a71);
}

function fn42_c58d3a71(ev)
{
	if(!ev) ev = window.event;
	var n = ((this != window) ? this : (ev ? ev.srcElement : null));

	if(!n) return;

	bpd_c58d3a71.b = 1;

	try {

		switch(n.id)
		{
			case 'c58d3a90':

				var f = (n.checked ? 1 : 0);

				cfg_c58d3a71 = fn04_c58d3a71(cfg_c58d3a71,
					'c58d3a71', 'dch', f);
				fn50_c58d3a71(f);

			break;

			case 'c58d3a91':

				fn48_c58d3a71();

			break;

			case 'c58d3a92':

				fn52_c58d3a71(n);

			break;

			case 'c58d3a93':

				if(!confirm(n.value + '?')) break;

				bpd_c58d3a71.c = 0;
				bpd_c58d3a71.s = '';
				fn26_c58d3a71('c58d3a97', '');

				fn49_c58d3a71(true);

				document.getElementById('c58d3a99').innerHTML = '';
				document.getElementById('c58d3a96').innerHTML = 0;
				document.getElementById('c58d3a90').focus();

			break;

			case 'c58d3a94':

				if(!n.value) break;

				var a = n.value.split('/'), del = (a[0].charAt(0) == '-');
				if(del) a[0] = a[0].substring(1);
				if(a[0].charAt(0) == '#') a[0] = a[0].substring(1);
				var u = parseInt(a[4] || a[0]);

				if((a[4] && a[3].charAt(0).toLowerCase() != 'b')
					|| isNaN(u) || u > 9000000 || u <= 0) break;

				a = new Array(); a[0] = u;
				if(fn45_c58d3a71(a, del) >= 0) n.value = '';

			break;

			case 'c58d3a95':

				if(ev.preventDefault) ev.preventDefault();
				else ev.returnValue = false;

				var fa = document.forms, c = null, j = 0;

				for(var i = 0; i < fa.length; i++)
				{
					if(fn11_c58d3a71(fa[i].name, 'bk')) { c = fa[i]; break; }
				}

				if(c)
				{
					c = c.getElementsByTagName('input');
					var a = new Array();

					for(var i = 1; i < c.length; i++)
					{
						if(c[i].checked && c[i].name > 0
							&& c[i].name <= 9000000) a[j++] = c[i].name;
					}

					fn45_c58d3a71(a, false);
				}

				if(!j) alert('Ничего не найдено.');

			break;

		default: break; }

	} catch (_err_) {;}

	bpd_c58d3a71.b = 0;
}

function fn43_c58d3a71(ev)
{
	if(!bpd_c58d3a71.h) return;

	try {

		if(!ev) ev = window.event;
		var n = (ev.srcElement || ev.target), p;

		if(n.href && !ev.ctrlKey && (p = n.href.split('/')).length > 5
			&& p[3].charAt(0).toLowerCase() == 'b'
			&& p[5].substring(0, 8).toLowerCase() == 'download'
			&& p[2].toLowerCase() == location.hostname.toLowerCase()
			&& isFinite(p[4]) && p[4] <= 9000000)
		{
			if(ev.preventDefault) ev.preventDefault();
			else ev.returnValue = false;

			var r, a = new Array(); a[0] = p[4];
			if((r = fn45_c58d3a71(a, false)) < 0) return;

			n.style.backgroundColor = (r ? '#C7F5C0' : '#E5E5E5');
			fn39_c58d3a71(n, 'mouseout', fn44_c58d3a71);
		}

	} catch (_err_) {;}
}

function fn44_c58d3a71()
{
	var n = ((this != window) ? this :
		(this.event ? this.event.srcElement : null));

	if(!n) return;

	if(n.removeEventListener) {
		n.removeEventListener('mouseout', fn44_c58d3a71, false);
	} else n.detachEvent('onmouseout', fn44_c58d3a71);

	n.style.backgroundColor = 'transparent';
}

function fn45_c58d3a71(u, del)
{
	var n = document.getElementById('c58d3a99');
	var r = u.length, i, j, ht = '';
	var a = new Array(0, 0, 0, 0), c;

	if(!n || !r) return -1;

	if(del)
	{
		for(i = 0; i < bpd_c58d3a71.c; i++)
		{
			if(bpd_c58d3a71.a[i] == u[0])
			{
				document.cookie = 'c58d3a97='
				+ bpd_c58d3a71.s.substring(0, i * 4)
				+ bpd_c58d3a71.s.substring(i * 4 + 4)
				+ '; path=/; expires=Mon, 31 Dec 2040 23:59:59 GMT';

				bpd_c58d3a71.b = 0;
				fn46_c58d3a71();

				return 1;
			}
		}

		return -1;
	}

	for(i = 0; i < bpd_c58d3a71.c; i++)
	{
		for(j = 0; j < u.length; j++)
		{ while(bpd_c58d3a71.a[i] == u[j]) { u.splice(j, 1); } }
	}

	if(!u.length) return 0;

	if((bpd_c58d3a71.c + u.length) > 400)
	{
		alert('Книг' + ((u.length > 1) ? 'и' : 'а') + ' не добавлен'
		+ ((u.length > 1) ? 'ы' : 'а') + '. Заняты ' + bpd_c58d3a71.c
		+ ' из 400 слотов.');

		return -1;
	}

	for(i = 0; i < u.length; i++)
	{
		c = u[i]; j = 0;

		do { a[j++] = ('0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'
			+ 'abcdefghijklmnopqrstuvwxyz').charAt(c % 62);
		} while((c /= 62) >= 1);

		bpd_c58d3a71.s += a.join('');
		a[0] = a[1] = a[2] = a[3] = 0;

		ht += '<a href="/b/' + u[i] + '">#' + u[i] + '</a> ';
		bpd_c58d3a71.a[bpd_c58d3a71.c++] = u[i];
	}

	document.cookie = 'c58d3a97=' + bpd_c58d3a71.s
	+ '; path=/; expires=Mon, 31 Dec 2040 23:59:59 GMT';

	n.innerHTML += ht;
	document.getElementById('c58d3a96').innerHTML = bpd_c58d3a71.c;
	fn49_c58d3a71(false);

	return (r == u.length);
}

function fn46_c58d3a71()
{
	if(bpd_c58d3a71.b) return;

	var s = fn03_c58d3a71('c58d3a97'), n, u, ht = '';

	if(s == null || bpd_c58d3a71.s == s ||
		(n = document.getElementById('c58d3a99')) == null) return;

	bpd_c58d3a71.s = s;
	bpd_c58d3a71.c = 0;

	for(var i = 0; i < s.length; i += 4)
	{
		if((u = fn47_c58d3a71(s.substring(i, i + 4))) == 0) break;
		bpd_c58d3a71.a[bpd_c58d3a71.c++] = u;
		ht += '<a href="/b/' + u + '">#' + u + '</a> ';
	}

	n.innerHTML = ht;
	document.getElementById('c58d3a96').innerHTML = bpd_c58d3a71.c;
	fn49_c58d3a71(bpd_c58d3a71.c == 0);
}

function fn47_c58d3a71(u)
{
	var r = 0, i = u.length, c;

	while(i--)
	{
		c = u.charCodeAt(i);
		r = 62 * r + (c - ((c > 90) ? 61 : ((c > 57) ? 55 : 48)));
	}

	return r;
}

function fn48_c58d3a71()
{
	if(!bpd_c58d3a71.c || !location.host) return;

	var fm = (document.getElementById('c58d3a89') || document).value;

	if(!fm || fm == 'fb2' || document.getElementById('user-login-form'))
		fm = 'download';

	var u = location.protocol + '//' + location.host + '/b/';
	var d = document.open('text/html', '_blank');

	if(!d) return;

	d.writeln('<html><head><title>Список файлов</title><style>a {'
	+ 'text-decoration:none; color:#000000; font:normal normal normal 15px/'
	+ '20px monospace; } body { background-color:#FDFEFF; margin-left:15px; }'
	+ '</style></head><body>');

	for(var i = 0; i < bpd_c58d3a71.c; i++)
	{
		d.writeln('<a href="' + u + bpd_c58d3a71.a[i] + '/' + fm + '" target='
		+ '"_blank" onclick="this.style.textDecoration = \'line-through\'">'
		+ u + bpd_c58d3a71.a[i] + '/' + fm + '</a><br />');
	}

	d.writeln('</body></html>');

	if(!window.opera || !window.opera.version
		|| window.opera.version() != '9.50') d.close();
}

function fn49_c58d3a71(f)
{
	document.getElementById('c58d3a91').disabled = f;
	document.getElementById('c58d3a92').disabled = f;
	document.getElementById('c58d3a93').disabled = f;
}

function fn50_c58d3a71(f)
{
	fn39_c58d3a71(document.body, 'click', fn43_c58d3a71);
	document.getElementById('c58d3a90').checked = f;
	bpd_c58d3a71.h = f;
}

function fn51_c58d3a71(ev)
{
	var f = 0, i, val = 'fb2', sel = 0, c, req = null;

	if(!ev) ev = window.event;
	var n = ((this != window) ? this : (ev ? ev.srcElement : null));

	if(!n) return;

	try {

		f = (n.id == 'c58d3a89');
		var s = document.getElementById(f ? 'useropt' : 'c58d3a89');

		if(s)
		{
			for(i = 0; i < n.options.length && i < s.options.length; i++)
			{ s.options[i].selected = n.options[i].selected; }
		}

		for(i = 0; i < n.options.length; i++)
		{
			if(n.options[i].selected)
			{
				val = (n.options[i].value || n.options[i].innerHTML);
				sel = i;
			}
		}

		if((c = fn03_c58d3a71('c58d3a87')) != null)
		{
			c = c.split(','); c[0] = sel;
			fn26_c58d3a71('c58d3a87', c.join(','));
		}

	} catch (_err_) {;}

	if(!f || !val || val.length > 20) return;

	try { req = new XMLHttpRequest(); }
	catch (_err_) {
		try { req = new ActiveXObject('Msxml2.XMLHTTP'); }
		catch (_err_) {
			try { req = new ActiveXObject('Microsoft.XMLHTTP'); }
			catch (_err_) {;}
		}
	}

	if(!req) return;

	try {

		req.open('GET', '/AJAX.php?op=setuseropt&o=D&v='
		+ encodeURIComponent(val), false);
		req.setRequestHeader('X-Requested-With', 'XMLHttpRequest');
		req.setRequestHeader('Accept', '*/*');
		req.send(null);

		delete req;

	} catch (_err_) {;}
}

function fn52_c58d3a71(n)
{
	var t = encodeURIComponent(document.getElementById('c58d3a89').value);

	if(!t || !bpd_c58d3a71.c || !location.host) return;
	if(bpd_c58d3a71.c > 100) { fn53_c58d3a71(t); return; }
	if(!confirm(n.value + ' ' + n.title + '?')) return;

	var q = '/mass/download?dtp=' + t + '&';

	for(var i = 0; i < bpd_c58d3a71.c; i++)
	{ q += bpd_c58d3a71.a[i] + '=on&'; }

	q += 'downloadall=uscript';

	window.open(q, '_blank');
}

function fn53_c58d3a71(t)
{
	var mi = Math.ceil(bpd_c58d3a71.c / 100);
	var mj = Math.ceil(bpd_c58d3a71.c / mi), p = 0;
	var d = document.open('text/html', '_blank');

	if(!d) return;

	d.writeln('<html><head><title>Mass Download</title></head>'
	+ '<body bgcolor="#FDFEFF" text="#000000"><div style="text-align:center;'
	+ 'margin-top:10%"><h4>Слишком много книг... Придется выкачивать по '
	+ 'частям:</h4>');

	for(var i = 0; i < mi; i++)
	{
		d.writeln('<form method="GET" action="/mass/download" target='
		+ '"_blank"><input type="hidden" name="dtp" value="' + t + '" />');

		for(var j = 0; j < mj && p < bpd_c58d3a71.c; j++)
		{
			d.writeln('<input type="hidden" name="'
			+ bpd_c58d3a71.a[p++] + '" value="on" />');
		}

		d.writeln('<input type="hidden" name="downloadall" value="uscript"'
		+ ' /><p><input type="submit" style="min-width:180px" value="'
		+ 'Запросить архив №' + (i + 1) + '" /></p></form>');
	}

	d.writeln('</div></body></html>');

	if(!window.opera || !window.opera.version
		|| window.opera.version() != '9.50') d.close();
}

function fn54_c58d3a71(nm, pf)
{
	var n = (nm.getElementsByTagName('h1')[0]
		|| nm.getElementsByTagName('h2')[0]);

	if(!n) return;

	n.innerHTML = '<span style="position:relative; float:right; cursor:'
	+ 'pointer; font-size:10px; margin-left:10px; margin-top:5px; line-height'
	+ ':15px" title="&#8596;">|' + (pf ? '&#8250;&#8249;' : '&#8249;&#8250;')
	+ '|</span>' + n.innerHTML;

	fn39_c58d3a71(n.firstChild, 'click', fn55_c58d3a71);
}

function fn55_c58d3a71()
{
	var f = ((fn05_c58d3a71(cfg_c58d3a71, 'rps') != '1') ? '1' : '0');
	cfg_c58d3a71 = fn04_c58d3a71(cfg_c58d3a71, 'c58d3a71', 'rps', f);

	location.reload(false);
}

function fn56_c58d3a71(mn)
{
	var hn = mn.getElementsByTagName('h3');

	if((hn[0] && hn[0].innerHTML.length > 4000)
		|| (hn[1] && hn[1].innerHTML.length > 4000)
		|| (hn[2] && hn[2].innerHTML.length > 4000))
	{
		fn30_c58d3a71('h3, p',
			'font-size:100%; font-weight:normal; text-align:left');
		fn30_c58d3a71('v', 'display:block');
		fn30_c58d3a71('stanza', 'margin:1px');
		fn30_c58d3a71('text-author, date', 'margin-left:20px');
		fn30_c58d3a71('emphasis, epigraph p', 'font-style:italic');

		hn = mn.appendChild(document.createElement('p'));
		hn.style.color = 'gray';
		hn.innerHTML = '[страница исправлена скриптом]';
	}
}

function fn00_ea29d0c6()
{
	var mn, n, bn = null;

	try {

		if((n = document.getElementById('c58d3a80')) != null)
		{
			edn_ea29d0c6 = document.getElementById('c58d3a81');
			bsf_ea29d0c6 = 1;
			bn = n;
		}

		if((mn = document.getElementById('genreform')) != null)
		{
			var a = mn.getElementsByTagName('input');

			for(var i = 0; i < a.length && (!n || !edn_ea29d0c6); i++)
			{
				var s = (a[i].type || '').toLowerCase();
				if(s == 'text') edn_ea29d0c6 = a[i];
				else { if(s == 'submit') n = a[i]; }
			}
		}

		if(!n && (mn = document.getElementById('tt')) != null)
		{
			bsf_ea29d0c6 = 1;
			edn_ea29d0c6 = document.getElementById('g');

			var a = mn.getElementsByTagName('th');

			for(var i = 0; i < a.length; i++)
			{ if(a[i].innerHTML.charCodeAt(0) == 1046) { n = a[i]; break; } }
		}

		if(!n)
		{
			abf_ea29d0c6 = 1;
			var a = document.body.getElementsByTagName('input');

			for(var i = 0; i < a.length; i++)
			{
				il = (a[i].name || '').toLowerCase();

				if(il == 'genre' || il == 'srcgenre')
				{ n = a[i]; break; }
			}

			if(n)
			{
				mn = n.parentNode;

				if(mn.innerHTML.charCodeAt(0) == 1046
					|| mn.innerHTML.charCodeAt(19) == 1078
					|| mn.innerHTML.charCodeAt(3) == 1046)
				{
					edn_ea29d0c6 = n;
					n = n.nextSibling;

				} else n = null;
			}
		}

	} catch (_err_) {;}

	if(!n || !edn_ea29d0c6) return;

	var lb = 'выбрать';

	try {

		if(!bsf_ea29d0c6)
		{
			if((bn = document.createElement('input')) != null)
			{
				bn.type = 'button';
				bn.value = lb;
				bn.style.marginLeft = bn.style.marginRight = '4px';
				bn = mn.insertBefore(bn, n);
			}
		}
		else
		{
			if(!bn)
			{
				n.innerHTML += '<a href="/g" style="font:normal normal '
				+ 'normal 9px/10px sans-serif" tabindex=0>(' + lb + ')</a>';
				bn = n.lastChild;
			}
		}

	} catch (_err_) {;}

	if(!bn) return;

	fn39_c58d3a71(bn, 'click', fn01_ea29d0c6);
	bn.title = lb + ' жанр';
}

function fn01_ea29d0c6(ev)
{
	if(!ev && (ev = window.event) == null) return;

	if(ev.preventDefault) ev.preventDefault();
	else ev.returnValue = false;

	if(!gsw_ea29d0c6)
	{
		var n, d1, bn, s;

		try {

			n = document.createElement('table');
			n = gsw_ea29d0c6 = document.body.appendChild(n);

			n.style.display = 'block';
			n.style.visibility = 'hidden';
			n.style.position = 'absolute';

			n.style.top  = ((document.body.scrollTop || window.pageYOffset ||
			(document.body.parentNode ? document.body.parentNode.scrollTop
			: 0)) + 100) + 'px';

			n.style.left = '250px';
			n.style.width = n.style.height = 'auto';
			n.style.zIndex = 32767;
			n.border = '2px';
			n.rules = 'none';
			n.style.backgroundColor = '#F3F7FB';
			n.cellPadding = n.cellSpacing = '2px';

			var tb = n.appendChild(document.createElement('tbody'));
			var r0 = tb.appendChild(document.createElement('tr'));
			var d0 = r0.appendChild(document.createElement('td'));
			var r1 = tb.appendChild(document.createElement('tr'));
			d1 = r1.appendChild(document.createElement('td'));

			s = fn04_ea29d0c6(d0);

		} catch (_err_) { return; }

		for(var i = 0; i < 2; i++)
		{
			bn = document.createElement('input');
			bn.type = 'button';
			bn.value = (i ? 'OK' : 'Отмена');
			bn.style.cssFloat = bn.style.styleFloat = 'right';
			bn.style.width = '70px';
			bn.style.margin = '4px';
			bn.id = 'b' + i + '_ea29d0c6';
			bn = d1.appendChild(bn);

			fn39_c58d3a71(bn, 'click', fn02_ea29d0c6);
		}

		var br = d1.appendChild(document.createElement('div'));
		br.style.marginTop = br.style.marginLeft = '4px';
		br.style.width = '' + (d1.offsetWidth - 170) + 'px';
		br.style.height = '' + bn.offsetHeight + 'px';
		br.style.cursor = 'move';
		br.unselectable = 'on';

		br.style.backgroundRepeat = 'repeat';
		br.style.backgroundImage = 'url("data:image/gif;base64,R0lGODlhBgAHA'
		+ 'BEAACH5BAEAAAAALAAAAAAGAAcAoQAAAMDAwP///4CAgAIIhI8ogTEJoykAOw==")';

		fn39_c58d3a71(br, 'mousedown', fn03_ea29d0c6);

		fn06_ea29d0c6(s);
		n.style.visibility = 'visible';
	}
	else
	{
		if(parseInt(gsw_ea29d0c6.style.top) < 0)
			gsw_ea29d0c6.style.top = '0px';

		if(parseInt(gsw_ea29d0c6.style.left) < 0)
			gsw_ea29d0c6.style.left = '0px';
	}

	var s = document.getElementById('s1_ea29d0c6');

	if(s && gsw_ea29d0c6)
	{
		var sl = Math.floor((window.innerHeight || (document.body.parentNode
			? document.body.parentNode.offsetHeight : 322)) / 23);
		if(sl > 5) s.size = sl;

		gsw_ea29d0c6.style.display = 'block';

		s.focus();
	}
}

function fn02_ea29d0c6()
{
	if(!gsw_ea29d0c6) return;

	gsw_ea29d0c6.style.display = 'none';
	edn_ea29d0c6.focus();

	var n = ((this != window) ? this :
		(this.event ? this.event.srcElement : null));

	var s = document.getElementById('s1_ea29d0c6');

	if(!n || !n.id || n.id.charAt(1) == '0' || !s) return;

	var es = '', ac = new Array(), l = 0;

	for(var i = 0; i < s.options.length; i++)
	{
		if(s.options[i].selected && s.options[i].value)
		{
			es += (es ? ',' : '') + s.options[i].value;
			ac[l++] = i;
		}
	}

	if(!es || !edn_ea29d0c6) return;

	if((bsf_ea29d0c6 || abf_ea29d0c6) &&
		(l = (edn_ea29d0c6.value || '').length) > 1)
	{
		var v = edn_ea29d0c6.value;

		while(v.charAt(--l) == ' ' && l) {;}
		if(v.charAt(l) != ',' && v.charAt(l) != ' ') es = ',' + es;

		edn_ea29d0c6.value += es;

	} else edn_ea29d0c6.value = es;

	fn05_ea29d0c6(ac, bsf_ea29d0c6);
}

function fn03_ea29d0c6(ev)
{
	try {

		if(!ev) ev = window.event;
		var et = ev.type.substring(5).toLowerCase();

		if(et == 'move')
		{
			var l = parseInt(gsw_ea29d0c6.style.left)
				- (mvs_ea29d0c6.x - ev.clientX);

			var t = parseInt(gsw_ea29d0c6.style.top)
				- (mvs_ea29d0c6.y - ev.clientY);

			var s = document.body;

			s = (s.scrollTop || window.pageYOffset ||
			(s.parentNode ? s.parentNode.scrollTop : 0));

			var h = mvs_ea29d0c6.i + s;

			if(t < s && t > 0 && mvs_ea29d0c6.y > ev.clientY)
			{ window.scrollBy(0, -20); t -= 20; }

			if(t > (h - gsw_ea29d0c6.clientHeight) && h < mvs_ea29d0c6.h)
			{ window.scrollBy(0, 20); t += 20; }

			gsw_ea29d0c6.style.left = l + 'px';
			gsw_ea29d0c6.style.top = t + 'px';

			mvs_ea29d0c6.x = ev.clientX;
			mvs_ea29d0c6.y = ev.clientY;

			return;
		}

		if(et == 'down')
		{
			mvs_ea29d0c6.x = ev.clientX;
			mvs_ea29d0c6.y = ev.clientY;

			mvs_ea29d0c6.i = (window.innerHeight || (document.body.parentNode
				? document.body.parentNode.offsetHeight : 100000));
			mvs_ea29d0c6.h = ((document.body.scrollHeight || 20) - 20);

			fn39_c58d3a71(document, 'mousemove', fn03_ea29d0c6);
			fn39_c58d3a71(document, 'mouseup', fn03_ea29d0c6);
			if(document.body.setCapture) document.body.setCapture();
		}

		if(et == 'up')
		{
			if(document.removeEventListener)
			{
				document.removeEventListener('mousemove',
					fn03_ea29d0c6, false);
				document.removeEventListener('mouseup', fn03_ea29d0c6, false);
			}
			else
			{
				document.detachEvent('onmousemove', fn03_ea29d0c6);
				document.detachEvent('onmouseup', fn03_ea29d0c6);
				document.body.releaseCapture();
			}
		}

	} catch (_err_) {;}
}

function fn04_ea29d0c6(w)
{
	var a = new Array('Деловая литература', '', 'Банковское дело', 'banking',
	'Бухучет, налогообложение, аудит', 'accounting',
	'Внешнеэкономическая деятельность', 'global_economy', 'Делопроизводство',
	'paper_work', 'Корпоративная культура', 'org_behavior',
	'Личные финансы', 'personal_finance', 'Малый бизнес', 'small_business',
	'Маркетинг, PR, реклама', 'marketing', 'Недвижимость', 'real_estate',
	'О бизнесе популярно', 'popular_business', 'Отраслевые издания',
	'industries', 'Поиск работы, карьера', 'job_hunting', 'Справочники',
	'economics_ref', 'Управление, подбор персонала', 'management',
	'Ценные бумаги, инвестиции', 'stock', 'Экономика', 'economics',
	'Детективы и Триллеры', '', 'Боевик', 'det_action',
	'Детектив', 'detective', 'Иронический детектив', 'det_irony',
	'Исторический детектив', 'det_history', 'Классический детектив',
	'det_classic', 'Криминальный детектив', 'det_crime', 'Крутой детектив',
	'det_hard', 'Маньяки', 'det_maniac', 'Политический детектив',
	'det_political', 'Полицейский детектив', 'det_police', 'Триллер',
	'thriller', 'Шпионский детектив', 'det_espionage', 'Детское', '',
	'Детская литература', 'children', 'Детская образовательная литература',
	'child_education', 'Детская проза', 'child_prose', 'Детская фантастика',
	'child_sf', 'Детские остросюжетные', 'child_det', 'Детские приключения',
	'child_adv', 'Детские стихи', 'child_verse', 'Сказка', 'child_tale',
	'Документальная литература', '', 'Биографии и Мемуары', 'nonf_biography',
	'Документальная литература', 'nonfiction', 'Искусство и Дизайн', 'design',
	'Критика', 'nonf_criticism', 'Публицистика', 'nonf_publicism',
	'Домоводство (Дом и семья)', '', 'Домашние животные', 'home_pets',
	'Домоводство', 'home', 'Здоровье', 'home_health', 'Кулинария',
	'home_cooking', 'Развлечения', 'home_entertain', 'Сад и огород',
	'home_garden', 'Сделай сам', 'home_diy', 'Спорт', 'home_sport',
	'Хобби и ремесла', 'home_crafts', 'Эротика, Секс', 'home_sex',
	'Компьютеры и Интернет', '', 'Базы данных', 'comp_db', 'Интернет',
	'comp_www', 'Компьютерное "железо"', 'comp_hard',
	'Околокомпьютерная литература', 'computers', 'ОС и Сети', 'comp_osnet',
	'Программирование', 'comp_programming', 'Программы', 'comp_soft',
	'Цифровая обработка сигналов', 'comp_dsp', 'Любовные романы', '',
	'Исторические любовные романы', 'love_history',
	'Короткие любовные романы', 'love_short',
	'Любовно-фантастические романы', 'love_sf', 'О любви', 'love',
	'Остросюжетные любовные романы', 'love_detective',
	'Современные любовные романы', 'love_contemporary', 'Эротика',
	'love_erotica', 'Наука, Образование', '', 'Альтернативная медицина',
	'sci_medicine_alternative', 'Аналитическая химия',
	'sci_anachem', 'Астрономия и Космос', 'sci_cosmos', 'Биология',
	'sci_biology', 'Биофизика', 'sci_biophys', 'Биохимия', 'sci_biochem',
	'Геология и география', 'sci_geo', 'Государство и право', 'sci_state',
	'Деловая литература', 'sci_business', 'История', 'sci_history',
	'Культурология', 'sci_culture', 'Литературоведение', 'sci_philology',
	'Математика', 'sci_math', 'Медицина', 'sci_medicine',
	'Научная литература', 'science', 'Органическая химия',
	'sci_orgchem', 'Политика', 'sci_politics', 'Психология',
	'sci_psychology', 'Религиоведение', 'sci_religion', 'Технические науки',
	'sci_tech', 'Физика', 'sci_phys', 'Физическая химия', 'sci_physchem',
	'Философия', 'sci_philosophy', 'Химия', 'sci_chem', 'Экономика',
	'sci_economy', 'Юриспруденция', 'sci_juris', 'Языкознание',
	'sci_linguistic', 'Поэзия, Драматургия', '', 'Драматургия', 'dramaturgy',
	'Поэзия', 'poetry', 'Приключения', '', 'Вестерн', 'adv_western',
	'Исторические приключения', 'adv_history', 'Морские приключения',
	'adv_maritime', 'Приключения', 'adventure', 'Приключения про индейцев',
	'adv_indian', 'Природа и животные', 'adv_animal',
	'Путешествия и география', 'adv_geo', 'Проза', '', 'Историческая проза',
	'prose_history', 'Классическая проза', 'prose_classic', 'Контркультура',
	'prose_counter', 'О войне', 'prose_military', 'Проза', 'prose',
	'Русская классическая проза', 'prose_rus_classic',
	'Советская классическая проза', 'prose_su_classics', 'Современная проза',
	'prose_contemporary', 'Прочее', '', 'Неотсортированное', 'other',
	'Партитуры', 'notes', 'Религия и духовность', '', 'Буддизм',
	'religion_budda', 'Религиозная литература', 'religion', 'Религия',
	'religion_rel', 'Самосовершенствование', 'religion_self', 'Эзотерика',
	'religion_esoterics', 'Справочная литература', '', 'Руководства',
	'ref_guide', 'Словари', 'ref_dict', 'Справочная литература', 'reference',
	'Справочники', 'ref_ref', 'Энциклопедии', 'ref_encyc', 'Старинное', '',
	'Античная литература', 'antique_ant', 'Древневосточная литература',
	'antique_east', 'Древнерусская литература', 'antique_russian',
	'Европейская старинная литература', 'antique_european',
	'Мифы. Легенды. Эпос', 'antique_myths', 'Старинная литература', 'antique',
	'Техника', '', 'Металлургия', 'sci_metal', 'Радиоэлектроника', 'sci_radio',
	'Строительство и сопромат', 'sci_build', 'Транспорт и авиация',
	'sci_transport', 'Фантастика', '', 'Альтернативная история', 'sf_history',
	'Боевая фантастика', 'sf_action', 'Героическая фантастика', 'sf_heroic',
	'Городское фэнтези', 'sf_fantasy_city', 'Детективная фантастика',
	'sf_detective', 'Киберпанк', 'sf_cyberpunk', 'Космическая фантастика',
	'sf_space', 'Научная Фантастика', 'sf', 'Постапокалипсис',
	'sf_postapocalyptic', 'Социально-психологическая фантастика', 'sf_social',
	'Ужасы и Мистика', 'sf_horror', 'Фэнтези', 'sf_fantasy',
	'Эпическая фантастика', 'sf_epic', 'Юмористическая фантастика',
	'sf_humor', 'Юмор', '', 'Анекдоты', 'humor_anecdote', 'Юмор', 'humor',
	'Юмористическая проза', 'humor_prose', 'Юмористические стихи',
	'humor_verse');

	var v = new Array('', 'det,thriller', 'child', 'nonf,design', '',
	'comp', '', 'sci', '', 'adv', '', '', '', 'ref', '',
	'sci_metal,sci_radio,sci_build,sci_transport', '', '');

	var r = new Array(94, 138, 234, 252, 284, 312, 330);

	var n = document.createElement('select');
	var g = n, iv = 0, ir = 0;

	if(!n || !a || !r || !v) return;

	n.size = '14';
	n.style.margin = '3px';
	n.style.padding = '2px';
	n.style.marginBottom = '-2px';
	if(bsf_ea29d0c6 || abf_ea29d0c6) n.multiple = true;
	n.id = 's1_ea29d0c6';

	for(var i = 0; i < a.length; i += 2)
	{
		if(a[i + 1] != '')
		{
			var o = g.appendChild(document.createElement('option'));
			o.innerHTML = a[i] + ' (' + a[i + 1] + ')';
			o.value = a[i + 1];

			if(bsf_ea29d0c6 && r[ir] == i)
			{
				o.style.color = '#A00000';
				o.innerHTML += ' *';
				ir++;
			}
		}
		else
		{
			if(bsf_ea29d0c6 && i && v[iv++] != '')
			{
				var o = g.appendChild(document.createElement('option'));
				o.innerHTML = '* (' + v[iv - 1] + ')';
				o.value = v[iv - 1];
				o.style.color = '#A00000';
			}

			g = n.appendChild(document.createElement('optgroup'));
			g.label = a[i];
			g.style.fontStyle = 'normal';
		}
	}

	delete a; delete v; delete r;
	fn39_c58d3a71(n, 'dblclick', fn02_ea29d0c6);

	return w.appendChild(n);
}

function fn05_ea29d0c6(a, f)
{
	var c = document.cookie, p = '0,0,0,0,0,0,0,0,0,0', i;
	var d = new Array(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	if(c && (i = c.indexOf('ea29d0c6')) >= 0)
	{
		c = (c.substring(i + 9)).split(';')[0];
		p = c.split('!')[f ? 0 : 1];
	}

	for(i = 0; i < a.length; i++)
	{ d[0 | (a[i] / 16)] |= 1 << (a[i] % 16); }

	d = d.join(',');

	document.cookie = 'ea29d0c6=' + (f ? p : d) + '!' + (f ? d : p)
	+ '; path=/; expires=Mon, 31 Dec 2040 23:59:59 GMT';
}

function fn06_ea29d0c6(n)
{
	var c = document.cookie, i, p = null, d, j, t = 0, s = 0;

	if(c && (i = c.indexOf('ea29d0c6')) >= 0)
	{
		c = (c.substring(i + 9)).split(';')[0];
		p = (c.split('!')[bsf_ea29d0c6]).split(',');
	}

	n.options[0].selected = !p;
	if(!p) return;

	for(i = 0; i < p.length; i++)
	{
		if(isNaN(d = parseInt(p[i]))) break;

		for(j = 1; j <= d; j *= 2)
		{
			if((d & j) && n.options[t])
			{
				n.options[t].selected = true;
				if(!bsf_ea29d0c6 && !abf_ea29d0c6) break;
			}

			t++;
		}

		s += 16; t = s;
	}
}

//конец uscript.js


//код из tbar.js

var edc_b163c450 = null, tga_b163c450 = null;

try {

	if(window.addEventListener)
	{
		window.addEventListener('DOMContentLoaded', fn0_b163c450, false);
		window.addEventListener('load', fn0_b163c450, false);
		document.addEventListener('load', fn0_b163c450, false);

	} else window.attachEvent('onload', fn0_b163c450);

} catch (_err_) {;}

function fn0_b163c450()
{
	if(edc_b163c450) return;

	var e = edc_b163c450 = (document.getElementById('edit-comment')
		|| document.getElementById('edit-body'));

	if(!e || (e.tagName || '').toLowerCase() != 'textarea') return;

	var a = new Array(
		'quote', 'Цитата', '[quote]$[/quote]',
		'url', 'Ссылка', '<a href="">$</a>',
		'b', 'Жирный шрифт', '[b]$[/b]',
		'i', 'Наклонный шрифт', '[i]$[/i]',
		's', 'Зачёркнутый текст', '[s]$[/s]',
		'u', 'Подчёркнутый текст', '[u]$[/u]',
		'img', 'Картинка', '[img]$[/img]',
		'code', 'Код', '<code>$</code>',
		'hr', 'Горизонтальная линия', '[hr]',
		'color', 'Цвет текста', '[color=red]$[/color]',
		'size', 'Размер шрифта', '[size=9]$[/size]',
		'font', 'Шрифт', '[font=monospace]$[/font]',
		'sup', 'Надстрочный текст', '[sup]$[/sup]',
		'ol', 'Нумерованный список', '<ol>$</ol>',
		'ul', 'Простой список', '<ul>$</ul>',
		'li', 'Элемент списка', '<li>',
		'<', 'Символ \"меньше\"', '&lt;',
		'>', 'Символ \"больше\"', '&gt;',
		'!', 'Символ ударения', '&#769;',
		'spoiler', 'Раскрывающаяся секция', '[collapse collapsed title=]$[/collapse]'
	);

	tga_b163c450 = new Array();

	if(e.addEventListener)
		e.addEventListener('blur', fn3_b163c450, false);
	else e.attachEvent('onblur', fn3_b163c450);

	var p = document.createElement('div'), r;

	p.style.font = 'normal normal normal 12px/13px courier new,monospace';
	p.style.color = '#9B9B9B';
	p.style.marginLeft= '-1px';
	p.style.marginBottom = '8px';

	if((r = document.getElementById('edit-teaser-js')) != null)
	{
		if(r.addEventListener)
			r.addEventListener('blur', fn3_b163c450, false);
		else r.attachEvent('onblur', fn3_b163c450);

		p.style.marginTop = '5px';
	}

	for(var i = 0, t = 0; i < a.length; i += 3)
	{
		var n = document.createElement('span');

		n.id = 'b163-' + t;
		n.innerHTML = '[' + a[i] + '] ';
		n.title = a[i + 1];

		n.style.cursor = 'pointer';
		n.style.marginRight = '-0.8ex';
		n.unselectable = 'on';

		n.onclick = fn1_b163c450;
		n.onmouseover = n.onmouseout = fn2_b163c450;

		p.appendChild(n);

		tga_b163c450[t++] = a[i + 2];
	}

	p = e.parentNode.insertBefore(p, e);
}

function fn1_b163c450(t)
{
	if(!t) t = window.event;
	t = tga_b163c450[(t.srcElement || t.target).id.substring(5)].split('$');

	var e = edc_b163c450, s1 = e.selectionStart, s2 = e.selectionEnd;

	e.focus();

	if(isNaN(s1) && document.selection)
	{
		var r1 = document.selection.createRange(), r2 = r1.duplicate();
		r2.moveToElementText(e);
		r2.setEndPoint('EndToEnd', r1);

		s1 = r2.text.length - r1.text.length;
		s2 = s1 + r1.text.length;
	}

	if(isNaN(s1) || isNaN(s2) || s1 < 0|| s2 < 0 || s1 > s2) s1 = s2 = 0;

	var c = e.value;

	e.value = c.substring(0, s1) + t[0] + c.substring(s1, s2)
	+ (t[1] || '') + c.substring(s2);

	if(navigator.userAgent.indexOf('MSIE') >= 0)
	{
		s1 -= (c.substring(0, s1).split('\r').length - 1);
		s2 -= (c.substring(0, s2).split('\r').length - 1);
	}

	s1 = s1 + t[0].length;
	s2 = t[1] ? (s2 + t[0].length) : s1;

	if(e.createTextRange)
	{
		var r = e.createTextRange();
		r.collapse();
		r.moveEnd('character', s2);
		r.moveStart('character', s1);
		r.select();

	} else if(e.setSelectionRange) e.setSelectionRange(s1, s2);
}

function fn2_b163c450(n)
{
	if(!n) n = window.event;

	(n.srcElement || n.target).style.color =
		(n.type.toLowerCase() == 'mouseover') ? '#585858' : '#9B9B9B';
}

function fn3_b163c450(n)
{
	if(!n) n = window.event;
	edc_b163c450 = (n.srcElement || n.target);
}

// конец tbar.js