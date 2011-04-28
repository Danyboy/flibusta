<?php

class Book
{

    private $id;
    private $title;
    private $title1;
    private $format;
    private $lang;
    private $annotation;
    private $coverImage;
    private $size;
    private $downloadsNumber;
    private $issueYear;

    public function getId()
    {
        return $this->id;
    }

    public function setId($value)
    {
        $this->id = $value;
    }

    public function getTitle()
    {
        return $this->title;
    }

    public function setTitle($value)
    {
        $this->title = $value;
    }

    public function getTitle1()
    {
        return $this->title1;
    }

    public function setTitle1($value)
    {
        $this->title1 = $value;
    }

    public function getFormat()
    {
        return $this->format;
    }

    public function setFormat($value)
    {
        $this->format = $value;
    }

    public function getLang()
    {
        return $this->lang;
    }

    public function setLang($value)
    {
        $this->lang = $value;
    }

    public function getAnnotation()
    {
        return $this->annotation;
    }

    public function setAnnotation($value)
    {
        $this->annotation = $value;
    }

    public function getCoverImage()
    {
        return $this->coverImage;
    }

    public function setCoverImage($value)
    {
        $this->coverImage = $value;
    }

    public function getSize() {
      return $this->size;
    }

    public function setSize($value) {
      $this->size = $value;
    }

    public function getDownloadsNumber() {
      return $this->downloadsNumber;
    }

    public function setDownloadsNumber($value) {
      $this->downloadsNumber = $value;
    }

    public function getIssueYear() {
      return $this->issueYear;
    }

    public function setIssueYear($value) {
      $this->issueYear = $value;
    }

}
