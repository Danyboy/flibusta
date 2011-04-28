<?php

class OPDSEntry
{
    protected $top;
    protected $value;

    public function addItem($entry, $value = null)
    {
        if (is_array($entry)) {
            array_push($this->value, $entry);
        } else {
            $this->value[$entry] = $value;
        }
    }

    public function addLink($url, $rel = null, $type = null, $doNotEncodeURL = false, $title = null)
    {
        $link = array('key' => 'link');
        $attributes = array('href' => $doNotEncodeURL ? $url : url($url, array('absolute' => TRUE)));

        if ($rel) {
            $attributes['rel'] = $rel;
        }
        if ($type) {
            $attributes['type'] = $type;
        }
        if ($title) {
            $attributes['title'] = $title;
        }
        $link['attributes'] = $attributes;

        $this->addItem($link);
    }

    public function toArray()
    {
        $this->top['value'] = $this->value;
        return $this->top;
    }

}
