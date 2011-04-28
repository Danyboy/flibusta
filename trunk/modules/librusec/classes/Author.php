<?php

class Author {
    private $id;
    private $firstName;
    private $middleName;
    private $lastName;
    private $homePage;
    private $nickname;
    private $booksNumber;

    public function getId() {
      return $this->id;
    }

    public function setId($value) {
      $this->id = $value;
    }

    public function getFirstName() {
      return $this->firstName;
    }

    public function setFirstName($value) {
      $this->firstName = $value;
    }

    public function getMiddleName() {
      return $this->middleName;
    }

    public function setMiddleName($value) {
      $this->middleName = $value;
    }

    public function getLastName() {
      return $this->lastName;
    }

    public function setLastName($value) {
      $this->lastName = $value;
    }

   public function getHomePage() {
     return $this->homePage;
   }

   public function setHomePage($value) {
     $this->homePage = $value;
   }

    public function getNickName() {
      return $this->nickname;
    }

    public function setNickName($value) {
      $this->nickname = $value;
    }

    public function getBooksNumber() {
      return $this->booksNumber;
    }

    public function setBooksNumber($value) {
      $this->booksNumber = $value;
    }

}
