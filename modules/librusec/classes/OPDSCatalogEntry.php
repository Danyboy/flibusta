<?php
module_load_include('php', 'librusec', 'classes/OPDSEntry');

class OPDSCatalogEntry extends OPDSEntry
{

    function __construct()
    {
        $this->value = array();
        $this->top = array(
            'key' => 'entry',
            'value' => $this->value);
        $this->addItem('updated', date(DateTime::ATOM));

    }


}
