<?php

module_load_include('php', 'librusec', 'classes/AbstractDAO');
module_load_include('php', 'librusec', 'classes/Author');
module_load_include('php', 'librusec', 'classes/AuthorAnnotation');


class AuthorDAO extends AbstractDAO
{

    /**
     * Найти автора на primary id
     * @param  $authorId primary id
     * @return Author|void
     */
    public function getAuthor($authorId)
    {
        $sth = db_query('select a.AvtorId, a.FirstName, a.MiddleName, a.LastName, a.NickName, a.HomePage FROM libavtorname a WHERE a.AvtorId = %d',
                        $authorId);
        if ($sth) {
            if ($row = db_fetch_object($sth)) {
                return $this->_toObject($row);
            }
        }
    }

    /**
     * @param  $authorId
     * @return AuthorAnnotation|void
     */
    public function getAuthorAnnotation($authorId)
    {
        $sth = db_query("select nid FROM libanode WHERE AvtorId = %d", $authorId);
        $nid = db_result($sth);
        if (!$nid) {
            $sth = db_query("select nid FROM node force KEY(node_title_type) WHERE title = '%s' AND type = 'adesc'", $authorId);
            $nid = db_result($sth);
        }
        if (IS_TEST_SERVER && !$nid) {
            $sth = db_query('select body from libaannotations where AvtorId=%d', $authorId); 
            if ($sth) {
                $text = db_result($sth);
                if ($text) {
                    $annotation = new AuthorAnnotation();
                    $annotation->setAuthorId($authorId);
                    $annotation->setAnnotation($text);
                    $sth = db_query('select distinct file from libapics where AvtorId=%d', $authorId);
                    if ($sth) {
                        $files = array();
                        while ($picture = db_result($sth)) {
                            $file = new stdClass();
                            $file->filepath = 'http://flibusta.net/sites/default/files/'.$picture;
                            $fileExtension = pathinfo($picture, PATHINFO_EXTENSION);
                            if ($fileExtension == 'jpg') {
                                $imageType = 'image/jpeg';
                            } else {
                                $imageType = 'image/'.$fileExtension;
                            }
                            $file->filemime = $imageType;
                            array_push($files, $file);
                        }
                        $annotation->setAttachedFiles($files);
                    }
                    return $annotation;
                }
            }

            return;
        }

        $sth = db_query("select vid, body FROM node_revisions WHERE nid = %d ORDER BY vid DESC limit 1", $nid);
        if ($row = db_fetch_object($sth)) {
            $vid = $row->vid;
            $body = $row->body;

            $result = db_query('SELECT f.* FROM {files} f INNER JOIN {upload} r ON f.fid = r.fid WHERE r.vid = %d ORDER BY r.weight, f.fid', $vid);
            while ($file = db_fetch_object($result)) {
                $files[$file->fid] = $file;
            }

            $annotation = new AuthorAnnotation();
            $annotation->setAuthorId($authorId);
            $annotation->setAnnotation($body);
            $annotation->setAttachedFiles($files);
            return $annotation;
        } else {
            return;
        }
    }

    /**
     * Найти авторов книги
     * @param  $bookId primary book id
     * @return array array of Author
     */
    public function findAuthorsByBook($bookId)
    {
        $authors = array();
        $sth = db_query('select a.AvtorId, a.FirstName, a.MiddleName, a.LastName, a.NickName, a.HomePage FROM libavtor ba, libavtorname a WHERE ba.BookId = %d and ba.AvtorId=a.AvtorId',
                        $bookId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                array_push($authors, $this->_toObject($row));
            }
        }

        return $authors;
    }

    /**
     * Найти авторов чьи книги созданы после указанной даты.
     *  Список сортируется по фамилии, имени, отчеству.
     *
     * @param int $intervalDays начальная дата в днях от текущего момента.
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @return array array of Author
     */
    public function findAuthorsByBookCreationDate($intervalDays, $pageNumber = 0, $pageSize = null)
    {
        $authors = array();
        $sth = db_query('select a.AvtorId, a.FirstName, a.MiddleName, a.LastName, a.NickName, a.HomePage, count(*) as BooksNumber FROM libavtor ba, libavtorname a, libbook b
        WHERE ba.BookId = b.BookId and ba.AvtorId=a.AvtorId and not (b.deleted&1) and date_add(b.time, interval %d day) > date(now()) '
                        . $this->getLanguageRestriction('b.Lang')
                        . ' group by a.AvtorId, a.FirstName, a.MiddleName, a.LastName, a.NickName, a.HomePage '
                        . ' order by a.LastName, a.FirstName, a.MiddleName '
                        . $this->makePagingLimit($pageNumber, $pageSize), $intervalDays);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                array_push($authors, $this->_toObject($row));
            }
        }

        return $authors;

    }

    /**
     * Найти переводчиков книги
     * @param  $bookId primary book id
     * @return array array of Author
     */
    public function findTranslatorsByBook($bookId)
    {
        $authors = array();
        $sth = db_query('select a.AvtorId, a.FirstName, a.MiddleName, a.LastName, a.NickName, a.HomePage FROM libtranslator ba, libavtorname a WHERE ba.BookId = %d and ba.TranslatorId=a.AvtorId',
                        $bookId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                array_push($authors, $this->_toObject($row));
            }
        }

        return $authors;
    }

    /**
     * Найти авторов по фамилии. Список сортируется по фамилии, имени, отчеству.
     * Авторы помеченные как дубликаты или не имеющие книг в список не включаются.
     *
     * @param string $namePrefix Если указано то используется как фильтр, иначе - ищется все.
     * @param int $pageNumber    Номер страницы
     * @param int $pageSize      Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @return array array of Author
     */
    public function findAuthorByName($namePrefix = null, $pageNumber = 0, $pageSize = null, $exactMatch = false)
    {
        $authors = array();

        $filter = $exactMatch ? " and a.LastName = '%s'" : ($namePrefix != null ? " and a.LastName like '%s%%'" : '');

        $sth = db_query('select a.AvtorId, a.FirstName, a.MiddleName, a.LastName, a.NickName, a.HomePage, count(*) as BooksNumber
        FROM libavtor ba, libavtorname a, libbook b
        WHERE ba.BookId = b.BookId and ba.AvtorId=a.AvtorId and not (b.deleted&1)
          and a.AvtorId not in (select BadId from libavtoraliase) '
        . $filter . ' '
        . $this->getLanguageRestriction('b.Lang') .'
        group by a.AvtorId, a.FirstName, a.MiddleName, a.LastName, a.NickName, a.HomePage
        order by a.LastName, a.FirstName, a.MiddleName'
        . $this->makePagingLimit($pageNumber, $pageSize)
            ,$namePrefix);

/*        $sth = db_query('select a.AvtorId, a.FirstName, a.MiddleName, a.LastName, a.NickName, a.HomePage FROM libavtorname a where a.AvtorId not in (select BadId from libavtoraliase) and a.AvtorId in
        (select b.AvtorId from libavtor b, libbook book where book.BookId = b.BookId and book.Deleted&1 = 0 ' . $this->getLanguageRestriction('book.Lang') . ') '
                        . $filter
                        . ' order by a.LastName, a.FirstName, a.MiddleName'
                        . $this->makePagingLimit($pageNumber, $pageSize),
                        $namePrefix);*/
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                array_push($authors, $this->_toObject($row));
            }
        }

        return $authors;
    }

    /**
     * Найти авторов чьи фамилии начинаются с указанного префикса и сгруппировать их по следующей после префикса букве.
     * Авторы помеченные как дубликаты или не имеющие книг в список не включаются.
     *
     * @param string $namePrefix Если указано то используется как фильтр, иначе - ищется все. Может быть пустым.
     * @param int $pageNumber    Номер страницы
     * @param int $pageSize      Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @return array array of array(name => count)
     */
    public function groupAuthorsByName($namePrefix)
    {
        $authors = array();

        $prefixLength = mb_strlen($namePrefix);
        $nameFragmentLength = $prefixLength + 1;

        $sth = db_query('select substr(a.LastName,1,%d) as LastName, count(*) as cnt FROM libavtorname a where
                        a.AvtorId not in (select BadId from libavtoraliase) and
                        a.AvtorId in (select b.AvtorId from libavtor b, libbook book where book.BookId = b.BookId and book.Deleted&1 = 0 ' . $this->getLanguageRestriction('book.Lang') . ') and
                        substr(a.LastName,1, %d) = "%s"
                        group by substr(a.LastName, 1, %d)',
                        $nameFragmentLength, $prefixLength, $namePrefix, $nameFragmentLength);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $authors[$row->LastName] = $row->cnt;
                //                array_push($authors, array($row->LastName => $row->cnt));
            }
        }

        return $authors;
    }

    private function _toObject($row)
    {
        $author = new Author();
        $author->setId($row->AvtorId);
        $author->setFirstName($row->FirstName);
        $author->setMiddleName($row->MiddleName);
        $author->setLastName($row->LastName);
        $author->setHomePage($row->HomePage);
        $author->setNickname($row->NickName);
        $author->setBooksNumber($row->BooksNumber);
        return $author;
    }

}
