<?php

module_load_include('php', 'librusec', 'classes/AbstractDAO');
module_load_include('php', 'librusec', 'classes/Book');


class BookDAO extends AbstractDAO
{

    /**
     * Найти книжки в заданном жанре
     * @param int $genreId    genre primary id
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @param boolean $includeAnnotation инициализировать или нет поле annotation
     * @return array array of Book
     */
    public function findBookByGenre($genreId, $pageNumber = 0, $pageSize = null, $includeAnnotation = false, $intervalDays = null)
    {
        $books = array();
        $dateFilter = $intervalDays == null ? '' : ' and date_add(b.time, interval '.$intervalDays.' day) > date(now()) ';
        $ordering = $intervalDays == null ? '  order by b.N desc, b.Title, b.Title1 ' : '  order by b.time desc, b.Title, b.Title1 ';
        $sth = db_query(
            'select b.BookId, b.Title, b.Title1, b.FileType, b.Lang, b.FileSize, b.N as DownloadsNumber, b.Year from libbook b, libgenre g where b.deleted&1 = 0 and b.BookId = g.BookId and g.GenreId = %d '
            . $this->getLanguageRestriction('b.Lang')
            . $dateFilter
            . $ordering
            . $this->makePagingLimit($pageNumber, $pageSize),
            $genreId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $book = $this->_toObject($row);
                if ($includeAnnotation) {
                    $book->setAnnotation($this->_getAnnotation($book->getId()));
                    $book->setCoverImage($this->_getCoverImage($book->getId()));
                }
                array_push($books, $book);
            }
        }

        return $books;
    }

    /**
     * Найти книжки по имени (поиск по подстроке)
     * @param string $bookName Имя книги. Если длинна стоки более 3-х символов то поиск делается по подстроке, иначе - по префиксу.
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @param boolean $includeAnnotation инициализировать или нет поле annotation
     * @return array array of Book
     */
    public function findBookByName($bookName, $pageNumber = 0, $pageSize = null, $includeAnnotation = false)
    {
        $books = array();

        $filter = strlen($bookName) > 3 ? 'b.Title like "%%%s%%"' : 'b.Title like "%s%%"';

        $sth = db_query(
            'select b.BookId, b.Title, b.Title1, b.FileType, b.Lang, b.FileSize, b.N as DownloadsNumber, b.Year from libbook b where b.deleted&1 = 0 and '.$filter
            . $this->getLanguageRestriction('b.Lang')
            . ' order by b.Title, b.Title1 '
            . $this->makePagingLimit($pageNumber, $pageSize),
            $bookName);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $book = $this->_toObject($row);
                if ($includeAnnotation) {
                    $book->setAnnotation($this->_getAnnotation($book->getId()));
                    $book->setCoverImage($this->_getCoverImage($book->getId()));
                }
                array_push($books, $book);
            }
        }

        return $books;
    }

    /**
     * Найти книжки по автору
     * @param int $authorId    author primary id
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @param boolean $includeAnnotation инициализировать или нет поле annotation
     * @return array array of Book
     */
    public function findBookByAuthor($authorId, $pageNumber = 0, $pageSize = null, $includeAnnotation = false, $intervalDays = null)
    {
        $books = array();
        $dateFilter = $intervalDays == null ? '' : ' and date_add(b.time, interval '.$intervalDays.' day) > date(now()) ';
        $ordering = $intervalDays == null ? '  order by b.Title, b.Title1 ' : '  order by b.time desc, b.Title, b.Title1 ';
        $sth = db_query(
            'select b.BookId, b.Title, b.Title1, b.FileType, b.Lang, b.FileSize, b.N as DownloadsNumber, b.Year from libbook b, libavtor a where b.deleted&1 = 0 and b.BookId = a.BookId and a.AvtorId = %d '
            . $this->getLanguageRestriction('b.Lang')
            . $dateFilter
            . $ordering
            . $this->makePagingLimit($pageNumber, $pageSize),
            $authorId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $book = $this->_toObject($row);
                if ($includeAnnotation) {
                    $book->setAnnotation($this->_getAnnotation($book->getId()));
                    $book->setCoverImage($this->_getCoverImage($book->getId()));
                }
                array_push($books, $book);
            }
        }

        return $books;
    }

    /**
     * Найти книжки по автору и серии, сортировка по номеру в серии
     * @param int $authorId    author primary id
     * @param int $sequenceId  sequence primary id
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @param boolean $includeAnnotation инициализировать или нет поле annotation
     * @return array array of Book
     */
    public function findBookByAuthorSequence($authorId, $sequenceId, $pageNumber = 0, $pageSize = null, $includeAnnotation = false)
    {
        $books = array();
        $sth = db_query(
            'select b.BookId, b.Title, b.Title1, b.FileType, b.Lang, b.FileSize, b.N as DownloadsNumber, b.Year from libbook b, libavtor a, libseq s where b.deleted&1 = 0 and b.BookId = a.BookId and a.AvtorId = %d and s.BookId = b.BookId and s.SeqId = %d'
            . $this->getLanguageRestriction('b.Lang')
            . ' order by s.SeqNumb, b.N desc '
            . $this->makePagingLimit($pageNumber, $pageSize),
            $authorId, $sequenceId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $book = $this->_toObject($row);
                if ($includeAnnotation) {
                    $book->setAnnotation($this->_getAnnotation($book->getId()));
                    $book->setCoverImage($this->_getCoverImage($book->getId()));
                }
                array_push($books, $book);
            }
        }

        return $books;
    }

/**
     * Найти книжки по серии, сортировка по номеру в серии
     * @param int $sequenceId  sequence primary id
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @param boolean $includeAnnotation инициализировать или нет поле annotation
     * @return array array of Book
     */
    public function findBookBySequence($sequenceId, $pageNumber = 0, $pageSize = null, $includeAnnotation = false, $intervalDays = null)
    {
        $books = array();
        $dateFilter = $intervalDays == null ? '' : ' and date_add(b.time, interval '.$intervalDays.' day) > date(now()) ';
        $ordering = $intervalDays == null ? '  order by s.SeqNumb, b.N desc ' : '  order by b.time desc, s.SeqNumb ';
        $sth = db_query(
            'select b.BookId, b.Title, b.Title1, b.FileType, b.Lang, b.FileSize, b.N as DownloadsNumber, b.Year from libbook b, libseq s where b.deleted&1 = 0 and s.BookId = b.BookId and s.SeqId = %d'
            . $this->getLanguageRestriction('b.Lang')
            . $dateFilter
            . $ordering
            . $this->makePagingLimit($pageNumber, $pageSize),
            $sequenceId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $book = $this->_toObject($row);
                if ($includeAnnotation) {
                    $book->setAnnotation($this->_getAnnotation($book->getId()));
                    $book->setCoverImage($this->_getCoverImage($book->getId()));
                }
                array_push($books, $book);
            }
        }

        return $books;
    }

    /**
     * Найти книжки по автору не включенные ни в какие серии
     * @param int $authorId    author primary id
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @param boolean $includeAnnotation инициализировать или нет поле annotation
     * @return array array of Book
     */
    public function findBookByAuthorWithoutSequence($authorId, $pageNumber = 0, $pageSize = null, $includeAnnotation = false)
    {
        $books = array();
        $sth = db_query(
            'select b.BookId, b.Title, b.Title1, b.FileType, b.Lang, b.FileSize, b.N as DownloadsNumber, b.Year from libbook b join libavtor a on (b.BookId = a.BookId) left join libseq s on (s.BookId = b.BookId) where b.deleted&1 = 0 and a.AvtorId = %d and s.SeqId is null'
            . $this->getLanguageRestriction('b.Lang')
            . ' order by b.Title, b.Title1 '
            . $this->makePagingLimit($pageNumber, $pageSize),
            $authorId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $book = $this->_toObject($row);
                if ($includeAnnotation) {
                    $book->setAnnotation($this->_getAnnotation($book->getId()));
                    $book->setCoverImage($this->_getCoverImage($book->getId()));
                }
                array_push($books, $book);
            }
        }

        return $books;
    }

    /**
     * Найти книгу по primary id
     * @param  $bookId primary id
     * @return Book|void
     */
    public function getBook($bookId)
    {
        $sth = db_query('select b.BookId, b.Title, b.Title1, b.FileType, b.Lang, b.FileSize, b.N as DownloadsNumber, b.Year from libbook b where b.deleted&1 = 0 and b.BookId = %d '. $this->getLanguageRestriction('b.Lang'), $bookId);
        if ($sth) {
            if ($row = db_fetch_object($sth)) {
                $book = $this->_toObject($row);
                $book->setAnnotation($this->_getAnnotation($book->getId()));
                $book->setCoverImage($this->_getCoverImage($book->getId()));
                return $book;
            }
        }
    }

    /**
     * Найти имя файла загруженного пользователем. Только для не fb2
     * @param  $bookId
     * @return string имя файла
     */
    public function getBookFileName($bookId) {
        $sth = db_query('select FileName from libfilename where bookId = %d', $bookId);
        if ($sth) {
            return db_result($sth);
        }
    }

    private function _toObject($row)
    {
        $book = new Book();
        $book->setId($row->BookId);
        $book->setTitle($row->Title);
        $book->setTitle1($row->Title1);
        $book->setFormat($row->FileType);
        $book->setLang($row->Lang);
        $book->setSize($row->FileSize);
        $book->setDownloadsNumber($row->DownloadsNumber);
        $book->setIssueYear($row->Year);
        return $book;
    }

    private function _getAnnotation($bookId)
    {
        // проверяем, что книга распарсена и лежит в кэше
        /*        $sth = db_query("select count(1) from libcache WHERE BookId = %d", $bookId);
        if (!db_result($sth)) { // если нет - парсим
            unset ($GLOBALS['PD']);
            libRead($bookId);
        }*/


        $sth = db_query("select nid FROM libbnode WHERE BookId = %d", $bookId);
        $nid = db_result($sth);
        if (!$nid) {
            $sth = db_query("select nid FROM node force KEY(node_title_type) WHERE title = '%s' AND type = 'bdesc'", $bookId);
            $nid = db_result($sth);
        }
        if (IS_TEST_SERVER && !$nid) {
            $sth = db_query('select body from libbannotations where bookid = %d', $bookId);
            if ($sth) {
                return db_result($sth);
            }
            return '';
        }

        $sth = db_query("select vid, body FROM node_revisions WHERE nid = %d ORDER BY vid DESC limit 1", $nid);
        if ($row = db_fetch_object($sth)) {
            return $row->body;
        } else {
            return '';
        }
    }

    private function _getCoverImage($bookId) {
        $sth = db_query('select cover from libcache where bookId=%d', $bookId);
        $cover = db_result($sth);
        if ($cover) {
            return $cover;
        }
        if (IS_TEST_SERVER) {
            $sth = db_query('select File from libbpics where bookId=%d', $bookId);
            if ($sth) {
                $cover = db_result($sth);
                if ($cover) {
                    return 'sites/default/files/'.$cover;
                }
            }
        }

    }

    /**
     * Найти книги созданные после указанной даты.
     * Список сортируется по дате создания (идентификатору книги, на самом деле).
     *
     * @param int $intervalDays начальная дата в днях от текущего момента.
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @param boolean $includeAnnotation инициализировать или нет поле annotation
     * @return array array of Book
     */
    public function findBookByCreationDate($intervalDays, $pageNumber = 0, $pageSize = null, $includeAnnotation = false)
    {
        $books = array();
        $sth = db_query('select b.BookId, b.Title, b.Title1, b.FileType, b.Lang, b.FileSize, b.N as DownloadsNumber, b.Year from libbook b where not (b.deleted&1) and date_add(b.time, interval %d day) > date(now()) '
        . $this->getLanguageRestriction('b.Lang')
        . 'order by b.bookid desc '
                        . $this->makePagingLimit($pageNumber, $pageSize), $intervalDays);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $book = $this->_toObject($row);
                if ($includeAnnotation) {
                    $book->setAnnotation($this->_getAnnotation($book->getId()));
                    $book->setCoverImage($this->_getCoverImage($book->getId()));
                }
                array_push($books, $book);
            }
        }
        return $books;
    }

    /**
     * Посчитать количество книг созданных после указанной даты
     * @param  $intervalDays
     * @return int
     */
    public function countBookByCreationDate($intervalDays)
    {
        $sth = db_query('select count(1) as cnt from libbook b where not (b.deleted&1) and date_add(b.time, interval %d day) > date(now()) '
        . $this->getLanguageRestriction('b.Lang'), $intervalDays);
        if ($sth) {
            return db_result($sth);
        }
        return false;
    }


    /**
     * Посчитать количество книг по названию (поиск по подстроке)
     * @param string $bookName Имя книги. Если длинна стоки более 3-х символов то поиск делается по подстроке, иначе - по префиксу.
     * @return int количество книг содержащих в названии подстроку
     */
    public function countBookByName($bookName)
    {
        $books = array();

        $filter = strlen($bookName) > 3 ? 'b.Title like "%%%s%%"' : 'b.Title like "%s%%"';

        $sth = db_query(
            'select count(1) as cnt from libbook b where b.deleted&1 = 0 and '.$filter
            . $this->getLanguageRestriction('b.Lang'),
            $bookName);
        if ($sth) {
            return db_result($sth);
        }
        return false;
    }

    /**
     * Посчитать количество книг автора
     * @param string $authorId author id
     * @return int количество книг автора
     */
    public function countBookByAuthor($authorId)
    {
        $sth = db_query(
            'select count(1) as cnt from libbook b, libavtor a where a.bookid = b.bookid and b.deleted = 0 and a.avtorid = %d '
                . $this->getLanguageRestriction('b.Lang'),
            $authorId);
        if ($sth) {
            $value = db_result($sth);
        } else {
            $value = false;
        }
        return $value;
    }
}
