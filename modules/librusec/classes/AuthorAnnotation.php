<?php

class AuthorAnnotation {
    private $authorId;
    private $annotation;
    private $attachedFiles;

    public function getAuthorId() {
      return $this->authorId;
    }

    public function setAuthorId($value) {
      $this->authorId = $value;
    }

    public function getAnnotation() {
      return $this->annotation;
    }

    public function setAnnotation($value) {
      $this->annotation = $value;
    }

    public function getAttachedFiles() {
      return $this->attachedFiles;
    }

    public function setAttachedFiles($value) {
      $this->attachedFiles = $value;
    }


}
