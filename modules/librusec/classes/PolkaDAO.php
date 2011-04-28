<?php

module_load_include('php', 'librusec', 'classes/AbstractDAO');
module_load_include('php', 'librusec', 'classes/PolkaPostponedBook');

class PolkaDAO {

    /**
     * Найти отложенные пользователм книги
     * @param  $userId registered user id
     * @return array array of PolkaPostponedBook
     */
    public function getPostponedBooks($userId) {
        $books = array();
        $sth = db_query('select p.id, p.BookId, p.AvtorId, p.Text, p.Flag, p.Time from libpolka p where p.userId = %d', $userId);

        if ($sth) {
            while ($row = db_fetch_object($sth)) {
                array_push($books, $this->_toObject($row));
            }
        }
        return $books;
    }

    private function _toObject($row) {
        $o = new PolkaPostponedBook();
        $o->setId($row->id);
        $o->setBookId($row->BookId);
        $o->setComment($row->Text);
        $o->setHideFlag($row->Flag);
        return $o;
    }
}
