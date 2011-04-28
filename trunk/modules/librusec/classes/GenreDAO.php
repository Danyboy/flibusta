<?php
module_load_include('php', 'librusec', 'classes/AbstractDAO');
module_load_include('php', 'librusec', 'classes/Genre');


class GenreDAO extends AbstractDAO
{

    /**
     * Найти классификацию жанров
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @return array array of Genre. Инициализируется только поле meta
     */
    public function findMetaGenre($pageNumber = 0, $pageSize = null)
    {
        $genres = array();

        $sth = db_query("select distinct GenreMeta from libgenrelist " . $this->makePagingLimit($pageNumber, $pageSize));
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                $genre = new Genre();
                $genre->setMeta($row->GenreMeta);
                array_push($genres, $genre);
            }
        }

        return $genres;
    }

    /**
     * Найти жанры по классификации
     * @param string $meta    Классификатор жанра, ищется по полному соответствию
     * @param int $pageNumber Номер страницы
     * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
     * @return array array of Genre.
     */
    public function findGenre($meta, $pageNumber = 0, $pageSize = null)
    {
        $genres = array();
        $sth = db_query("select gl.GenreId, gl.GenreCode, gl.GenreDesc, gl.GenreMeta, count(*) as BooksNumber
        from libgenrelist gl, libgenre g, libbook b
        where genremeta = '%s' and gl.GenreId = g.GenreId and g.BookId = b.BookId and b.Deleted&1 = 0 " . $this->getLanguageRestriction('b.Lang')
        . ' group by gl.GenreId, gl.GenreCode, gl.GenreDesc, gl.GenreMeta '
        . $this->makePagingLimit($pageNumber, $pageSize), $meta);
        
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                array_push($genres, $this->_toObject($row));
            }
        }

        return $genres;
    }

    /**
     * Найти жанры к которым относится книга.
     * @param  $bookId primary book key
     * @return array array of Genre assigned to book
     */
    public function findGenreByBook($bookId)
    {
        $sth = db_query('select g.GenreId, g.GenreCode, g.GenreDesc, g.GenreMeta from libgenrelist g, libgenre b where g.GenreId=b.GenreId and b.BookId = %d', $bookId);
        $genres = array();
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                array_push($genres, $this->_toObject($row));
            }
        }

        return $genres;

    }

    /**
       * Найти жанры в которых книги созданы после указанной даты.
       * Список сортируется по алфавиту
       *
       * @param int $intervalDays начальная дата в днях от текущего момента.
       * @param int $pageNumber Номер страницы
       * @param int $pageSize   Если указано то возвращается страница $pageNumber, иначе - все найденное
       * @return array array of Genre
       */
      public function findGenresByBookCreationDate($intervalDays, $pageNumber = 0, $pageSize = null)
      {
          $result = array();
          $sth = db_query(
              'select g.GenreId, g.GenreCode, g.GenreDesc, g.GenreMeta, count(*) as BooksNumber from libgenrelist g, libgenre gb, libbook b
              where b.deleted&1 = 0 and g.GenreId=gb.GenreId and gb.BookId = b.BookId and date_add(b.time, interval %d day) > date(now()) '
              . $this->getLanguageRestriction('b.Lang')
              . 'group by g.GenreId, g.GenreCode, g.GenreDesc, g.GenreMeta '
              . 'order by g.GenreDesc '
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
     * Найти жанр по идентификатору.
     * @param  $genreId primary id
     * @return void|Genre возвращает void если не найдено.
     */
    public function getGenre($genreId)
    {
        $sth = db_query('select g.GenreId, g.GenreCode, g.GenreDesc, g.GenreMeta from libgenrelist g where g.GenreId = %d', $genreId);
        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                return $this->_toObject($row);
            }
        }
    }

    private function _toObject($dbRow)
    {
        $genre = new Genre();
        $genre->setId($dbRow->GenreId);
        $genre->setCode($dbRow->GenreCode);
        $genre->setDescription($dbRow->GenreDesc);
        $genre->setMeta($dbRow->GenreMeta);
        $genre->setBooksNumber($dbRow->BooksNumber);
        return $genre;
    }

}
