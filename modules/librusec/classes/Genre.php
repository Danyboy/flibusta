<?php

class Genre {
    private $id;
    private $code;
    private $description;
    private $meta;
    private $booksNumber;

    public function getId() {
      return $this->id;
    }

    public function setId($value) {
      $this->id = $value;
    }

    public function getCode() {
      return $this->code;
    }

    public function setCode($value) {
      $this->code = $value;
    }

    public function getDescription() {
      return $this->description;
    }

    public function setDescription($value) {
      $this->description = $value;
    }

    public function getMeta() {
      return $this->meta;
    }

    public function setMeta($value) {
      $this->meta = $value;
    }

    public function getBooksNumber() {
      return $this->booksNumber;
    }

    public function setBooksNumber($value) {
      $this->booksNumber = $value;
    }
    
    
}
