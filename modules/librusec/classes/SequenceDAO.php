<?php

module_load_include('php', 'librusec', 'classes/AbstractDAO');
module_load_include('php', 'librusec', 'classes/Sequence');

class SequenceDAO extends AbstractDAO
{

    public function findSequenceByName($namePrefix, $pageNumber, $pageSize, $exactMatch = false)     {
        $result = array();
        $filter = $exactMatch ? " and n.SeqName = '%s'" : ($namePrefix != null ? " and n.SeqName like '%s%%'" : '');
        $sth = db_query(
            'select n.SeqId, n.SeqName, count(*) as BooksNumber from libseqname n, libseq s, libbook b
            where b.deleted&1 = 0 and n.seqId = s.SeqId and s.BookId = b.BookId  '
            . $this->getLanguageRestriction('b.Lang')
            . $filter
            . ' group by n.SeqId, n.SeqName order by n.SeqName '
            . $this->makePagingLimit($pageNumber, $pageSize),
            $namePrefix);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $sequence = $this->_toObject($row);
                array_push($result, $sequence);
            }
        }
        return $result;
    }

    public function groupSequencesByName($namePrefix) {
        $authors = array();

        $prefixLength = mb_strlen($namePrefix);
        $nameFragmentLength = $prefixLength + 1;

        $sth = db_query(
            'select substr(n.SeqName,1, %d) as SeqName, count(*) as cnt from libseqname n
            where substr(n.SeqName,1, %d) = "%s" and n.SeqId in (select SeqId from libseq s, libbook b where s.BookId = b.BookId and b.Deleted&1 = 0  '
            . $this->getLanguageRestriction('b.Lang') . ') '
            . 'group by substr(n.SeqName,1, %d) ',
            $nameFragmentLength, $prefixLength, $namePrefix, $nameFragmentLength);

        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $authors[$row->SeqName] = $row->cnt;
            }
        }

        return $authors;

    }
    /**
     * Поиск серий по автору книг. Список сортируется по имени серии
     * @param int $authorId    author primary id
     * @param int $pageNumber    Номер страницы
     * @param int $pageSize      Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @return array array of Sequence
     */
    public function findSequenceByAuthor($authorId, $pageNumber = 0, $pageSize = null)
    {
        $result = array();
        $sth = db_query(
            'select n.SeqId, n.SeqName, count(*) as BooksNumber from libseqname n, libseq s, libbook b, libavtor a
            where b.deleted&1 = 0 and b.BookId = a.BookId and n.seqId = s.SeqId and s.BookId = b.BookId and a.AvtorId = %d '
            . $this->getLanguageRestriction('b.Lang')
            . 'group by n.SeqId, n.SeqName order by n.SeqName '
            . $this->makePagingLimit($pageNumber, $pageSize),
            $authorId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $sequence = $this->_toObject($row);
                array_push($result, $sequence);
            }
        }
        return $result;
    }

    /**
     * Поиск серий по книге. Список сортируется по имени серии
     * @param int $bookId        book primary id
     * @param int $pageNumber    Номер страницы
     * @param int $pageSize      Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @return array array of Sequence. Sequence->getBooksInSequence заполняется номером книги в серии
     */
    public function findSequenceByBook($bookId, $pageNumber = 0, $pageSize = null)
    {
        $result = array();
        $sth = db_query(
            'select n.SeqId, n.SeqName, s.SeqNumb as BooksNumber from libseqname n, libseq s, libbook b
            where b.deleted&1 = 0 and n.seqId = s.SeqId and s.BookId = b.BookId and b.BookId = %d '
            . $this->getLanguageRestriction('b.Lang')
            . 'group by n.SeqId, n.SeqName order by n.SeqName '
            . $this->makePagingLimit($pageNumber, $pageSize),
            $bookId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $sequence = $this->_toObject($row);
                array_push($result, $sequence);
            }
        }
        return $result;
    }

    /**
     * Найти серии в которых книги созданы после указанной даты.
     * Список сортируется по алфавиту
     *
     * @param int $intervalDays начальная дата в днях от текущего момента.
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @return array array of Sequence
     */
    public function findSequencesByBookCreationDate($intervalDays, $pageNumber = 0, $pageSize = null)
    {
        $result = array();
        $sth = db_query(
            'select n.SeqId, n.SeqName, count(*) as BooksNumber from libseqname n, libseq s, libbook b
            where b.deleted&1 = 0 and n.seqId = s.SeqId and s.BookId = b.BookId and date_add(b.time, interval %d day) > date(now()) '
            . $this->getLanguageRestriction('b.Lang')
            . 'group by n.SeqId, n.SeqName order by n.SeqName '
            . $this->makePagingLimit($pageNumber, $pageSize),
            $intervalDays);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $sequence = $this->_toObject($row);
                array_push($result, $sequence);
            }
        }
        return $result;
    }


    /**
     * Получить серию по идентификатору
     * @param  $sequenceId sequence primary id
     * @return Sequence найденная серия. Поле BooksNumber не инициализируется.
     */
    public function getSequence($sequenceId)
    {
        $sth = db_query(
            'select n.SeqId, n.SeqName from libseqname n where n.SeqId = %d',
            $sequenceId);
        if ($sth) {
            $row = db_fetch_object($sth);
            if ($row) {
                return $this->_toObject($row);
            }
        }

    }


    private function _toObject($row)
    {
        $s = new Sequence();
        $s->setId($row->SeqId);
        $s->setName($row->SeqName);
        $s->setBooksInSequence($row->BooksNumber);

        return $s;
    }

}
