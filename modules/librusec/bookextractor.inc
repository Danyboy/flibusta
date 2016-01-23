<?php
/**
 * Company: Etersoft http://etersoft.ru 
 * User: Stas Korobeynikov
 * Email: stas@etersoft.ru
 * Date: 29.07.15
 */

class ArcName {
    public $name;
    public $from;
    public $to;

    public function isFit($id) {
        return ($id >= $this->from && $id <= $this->to);
    }
}

class BookExtractor {
    private $fromPath;
    private $toPath;

    function __construct($fromPath, $toPath) {
        $this->fromPath = $fromPath;
        $this->toPath = $toPath;
    }

    private function getListFiles() {
        return scandir($this->fromPath);
    }

    private function smartedList($list) {
        $pattern = "/^(f|d){0,1}?\\.{0,1}?fb2\\-([0-9]+)\\-([0-9]+).zip/";
        $filelist = [];
        foreach ($list as $value) {
            if(preg_match($pattern, $value, $matches)) {
                $newfile = new ArcName();
                $newfile->name = $value;
                $newfile->from = $matches[2];
                $newfile->to = $matches[3];
                array_push($filelist, $newfile);
            }
        }
        return $filelist;
    }

    private function findAtSmartedList($sl, $id) {
        $filter = array_filter($sl, function($var) use ($id) {return $var->isFit($id);});
        $currentFilter = current($filter);
        if(!isset($currentFilter)) {
            echo "Book not found\n";
        }
        if(empty($filter)) {
            echo "Archive with book not found\n";
            return null;
        }
        return $currentFilter;
    }

    private function unArch($filename, $id) {
        $zip = new ZipArchive;
        if ($zip->open( $this->fromPath."/".$filename ) == true) {
            $extractedfilename = "".$id.".fb2";
            //echo "Arg {$filename} {$id} \n";
            $zip->extractTo ( $this->toPath , $extractedfilename );
            $zip->close();
            return $extractedfilename;
        }
        else {
            return null;
        }

    }

    private function getArhievePath($id) {
        $filelist =  $this->getListFiles();
        $sl = $this->smartedList($filelist);
        $smartedFile = $this->findAtSmartedList($sl, $id);
        if(!isset($smartedFile)) {
            return null;
        }
        return $this->unArch($smartedFile->name, $id);
    }

    public function getBook($id) {
        return $this->getArhievePath($id);
    }
}


if (!empty($argv)){
    $be = new BookExtractor( "/mnt/sshfs/fb2.Flibusta.Net/", "/var/www/html/b/");
    print ($be->getBook($argv[1]));
}