<?php

class Sequence {
    private $id;
    private $name;
    private $booksInSequence;

    public function getId() {
      return $this->id;
    }

    public function setId($value) {
      $this->id = $value;
    }

    public function getName() {
      return $this->name;
    }

    public function setName($value) {
      $this->name = $value;
    }

    public function getBooksInSequence() {
      return $this->booksInSequence;
    }

    public function setBooksInSequence($value) {
      $this->booksInSequence = $value;
    }

}
