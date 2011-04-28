<?php
module_load_include('php', 'librusec', 'classes/OPDSEntry');
module_load_include('php', 'librusec', 'classes/OPDSCatalogEntry');


class OPDSCatalog extends OPDSEntry
{


    function __construct()
    {
        $this->value = array();
        $this->top = array(
            'key' => 'feed',
            'attributes' => array(
                'xmlns' => 'http://www.w3.org/2005/Atom',
                'xmlns:dc' => 'http://purl.org/dc/terms/',
                'xmlns:os' => 'http://a9.com/-/spec/opensearch/1.1/',
                'xmlns:opds' => 'http://opds-spec.org/2010/catalog'
            ));
    }


    public function addEntry(OPDSCatalogEntry $entry)
    {
        array_push($this->value, $entry->toArray());
    }


}
