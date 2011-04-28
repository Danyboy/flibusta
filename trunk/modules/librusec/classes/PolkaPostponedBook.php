<?php

/**
 * Книга отложенная пользователем
 */
class PolkaPostponedBook {
    private $id;
    private $bookId;
    private $comment;
    private $hideFlag;

    public function getId() {
      return $this->id;
    }

    public function setId($value) {
      $this->id = $value;
    }

    public function getBookId() {
      return $this->bookId;
    }

    public function setBookId($value) {
      $this->bookId = $value;
    }

    public function getComment() {
      return $this->comment;
    }

    public function setComment($value) {
      $this->comment = $value;
    }

    public function getHideFlag() {
      return $this->hideFlag;
    }

    public function setHideFlag($value) {
      $this->hideFlag = $value;
    }


}
