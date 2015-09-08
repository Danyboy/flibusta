<?php

define('DEBUG_SERVER_PREFIX', 'http://' . $_SERVER['HTTP_HOST'] . '/'); // @TODO REMOVE LINK HARDCODE
define('IS_TEST_SERVER', false); // @TODO Remove stub
//define('IS_TEST_SERVER', true); // @TODO Remove stub
//const DEBUG_SERVER_PREFIX = ''; // production configuration

define('OPDS_NEW_BOOKS_SEARCH_INTERVAL', 7); // 7 days

define('OPDS_CATALOG_NEW', 'new');
define('OPDS_CATALOG_NEW_GENRES', 'newgenres');
define('OPDS_CATALOG_NEW_SEQUENCES', 'newsequences');
define('OPDS_CATALOG_NEW_AUTHORS', 'newauthors');

define('OPDS_CATALOG_GENRES', 'genres');
define('OPDS_CATALOG_SEQUENCES_INDEX', 'sequencesindex');
define('OPDS_CATALOG_SEQUENCES', 'sequences');
define('OPDS_SEQENCE_BOOKS_CATALOG', 'sequencebooks');
define('OPDS_CATALOG_AUTHORS_INDEX', 'authorsindex');
define('OPDS_CATALOG_AUTHORS', 'authors');
define('OPDS_AUTHOR_BOOKS_CATALOG', 'author');
define('OPDS_AUTHOR_SEQENCES_CATALOG', 'authorsequences');
define('OPDS_AUTHOR_SEQENCE_BOOKS_CATALOG', 'authorsequence');
define('OPDS_AUTHOR_SEQENCELESS_BOOKS_CATALOG', 'authorsequenceless');

//define('OPDS_BOOK_ENTRY', 'book');

define('OPDS_CATALOG_SEARCH_ALL', 'opensearch');
define('OPDS_CATALOG_SEARCH', 'search');
define('OPDS_CATALOG_SEARCH_BOOKS', 'books');
define('OPDS_CATALOG_SEARCH_AUTHORS', 'authors');

define('OPDS_CATALOG_POLKA', 'polka');


module_load_include('php', 'librusec', 'classes/GenreDAO');
module_load_include('php', 'librusec', 'classes/BookDAO');
module_load_include('php', 'librusec', 'classes/AuthorDAO');
module_load_include('php', 'librusec', 'classes/PolkaDAO');
module_load_include('php', 'librusec', 'classes/SequenceDAO');
module_load_include('php', 'librusec', 'classes/OPDSCatalog');
module_load_include('php', 'librusec', 'classes/OPDSCatalogEntry');


function libOPDSCatalog()
{

//    __tryCachedOutput(0, '_makeCatalogRedirect', array());
//    return;

    $cacheInterval = variable_get('librusec_OPDSCacheInterval', OPDS_CacheInterval);
    $section = arg(1);
    $userAgent = $_SERVER['HTTP_USER_AGENT'];
    $enableConverters = variable_get('librusec_Convert', FALSE) && !strstr($userAgent, "FBReader");
    $disabeFeedTypeMix = !strstr($userAgent, "FBReader") && !strstr($userAgent, "Moon+ Reader"); // (boolean)strstr($userAgent, "Aldiko");


    switch ($section) {
        case OPDS_CATALOG_NEW:
            $pageNumber = arg(2);
            $type = arg(3);
            $typeId = arg(4);
            $cacheInterval = variable_get('librusec_OPDSCacheNewInterval', OPDS_CacheNewInterval);
            __tryCachedOutput($cacheInterval, '_makeNewCatalog', array($pageNumber, $type, $typeId, $enableConverters));
//            $catalog = _makeNewCatalog($pageNumber, $type, $typeId, $enableConverters);
            break;
        case OPDS_CATALOG_NEW_GENRES:
            $pageNumber = arg(2);
            $cacheInterval = variable_get('librusec_OPDSCacheNewInterval', OPDS_CacheNewInterval);
            __tryCachedOutput($cacheInterval, '_makeNewGenresCatalog', array($pageNumber));
            break;
        case OPDS_CATALOG_NEW_AUTHORS:
            $pageNumber = arg(2);
            $cacheInterval = variable_get('librusec_OPDSCacheNewInterval', OPDS_CacheNewInterval);
            __tryCachedOutput($cacheInterval, '_makeNewAuthorsCatalog', array($pageNumber));
            break;
        case OPDS_CATALOG_NEW_SEQUENCES:
            $pageNumber = arg(2);
            $cacheInterval = variable_get('librusec_OPDSCacheNewInterval', OPDS_CacheNewInterval);
            __tryCachedOutput($cacheInterval, '_makeNewSequencesCatalog', array($pageNumber));
            break;
        case OPDS_CATALOG_GENRES:
            $genreMeta = arg(2);
            if ($genreMeta) {
                $genreId = arg(3);
                if (isset($genreId)) {
                    $pageNumber = arg(4);
                    __tryCachedOutput($cacheInterval, '_makeBooksCatalogByGenre', array($genreId, $pageNumber, $enableConverters));
                    //                    $catalog = _makeBooksCatalogByGenre($genreId, $pageNumber);
                } else {
                    __tryCachedOutput($cacheInterval, '_makeGenresCatalog', array($genreMeta));
                    //                    $catalog = _makeGenresCatalog($genreMeta);
                }
            } else {
                __tryCachedOutput($cacheInterval, '_makeGenresCatalog', array());
                $catalog = _makeGenresCatalog();
            }
            break;
        case OPDS_CATALOG_AUTHORS_INDEX:
            $namePrefix = arg(2);
            __tryCachedOutput($cacheInterval, '_makeAuthorsIndex', array($namePrefix));
//            $catalog = _makeAuthorsIndex($namePrefix, $pageNumber);
            break;
        case OPDS_CATALOG_AUTHORS:
            $namePrefix = arg(2);
            $pageNumber = arg(3);
            __tryCachedOutput($cacheInterval, '_makeAuthorsCatalog', array($namePrefix, $pageNumber));
//            $catalog = _makeAuthorsCatalog($namePrefix, $pageNumber);
            break;

        case OPDS_AUTHOR_BOOKS_CATALOG:
            $authorId = arg(2);
            $pageNumber = arg(3);
            __tryCachedOutput($cacheInterval, '_makeBooksCatalogByAuthor', array($authorId, $pageNumber, $enableConverters, $disabeFeedTypeMix));
//            $catalog = _makeBooksCatalogByAuthor($authorId, $pageNumber);
            break;

        case OPDS_AUTHOR_SEQENCES_CATALOG:
            $authorId = arg(2);
            $pageNumber = arg(3);
            __tryCachedOutput($cacheInterval, '_makeSequencesCatalogByAuthor', array($authorId, $pageNumber));
//            $catalog = _makeSequencesCatalogByAuthor($authorId, $pageNumber);
            break;

        case OPDS_AUTHOR_SEQENCE_BOOKS_CATALOG:
            $authorId = arg(2);
            $sequenceId = arg(3);
            $pageNumber = arg(4);
            __tryCachedOutput($cacheInterval, '_makeSequenceBooksCatalogByAuthor', array($authorId, $sequenceId, $pageNumber, $enableConverters));
//            $catalog = _makeSequenceBooksCatalogByAuthor($authorId, $sequenceId, $pageNumber);
            break;

        case OPDS_AUTHOR_SEQENCELESS_BOOKS_CATALOG:
            $authorId = arg(2);
            $pageNumber = arg(3);
            __tryCachedOutput($cacheInterval, '_makeSequencelessBooksCatalogByAuthor', array($authorId, $pageNumber, $enableConverters));
//            $catalog = _makeSequenceBooksCatalogByAuthor($authorId, $sequenceId, $pageNumber);
            break;

        case OPDS_CATALOG_SEARCH:
            $searchTerm = $_GET['searchTerm'];
            $searchType = $_GET['searchType'];
            $pageNumber = $_GET['pageNumber'];
            __tryCachedOutput(0, '_makeCatalogBySearch', array($searchTerm, $searchType, $pageNumber, $enableConverters));
            break;

        case OPDS_CATALOG_SEARCH_ALL:
            $searchTerm = $_GET['searchTerm'];
            $pageNumber = $_GET['pageNumber'];
            __tryCachedOutput(0, '_makeCatalogBySearchAll', array($searchTerm, $pageNumber, $enableConverters));
            break;

        case OPDS_CATALOG_SEQUENCES_INDEX:
            $namePrefix = arg(2);
            __tryCachedOutput($cacheInterval, '_makeSequencesIndex', array($namePrefix));
//            _makeSequencesIndex($namePrefix);
            break;

        case OPDS_CATALOG_SEQUENCES:
            $namePrefix = arg(2);
            $pageNumber = arg(3);
            __tryCachedOutput($cacheInterval, '_makeSequencesCatalog', array($namePrefix, $pageNumber));
//            $catalog = _makeSequencesCatalog($namePrefix, $pageNumber);
            break;


        case OPDS_SEQENCE_BOOKS_CATALOG:
            $sequenceId = arg(2);
            $pageNumber = arg(3);
            __tryCachedOutput($cacheInterval, '_makeSequenceBooksCatalog', array($sequenceId, $pageNumber, $enableConverters));
//            _makeSequenceBooksCatalog($sequenceId, $pageNumber)
            break;

        case OPDS_CATALOG_POLKA:
            __tryCachedAuthenticatedOutput(0, '_makeShelvedBooksCatalog', array($enableConverters));
            break;

        /*        case OPDS_BOOK_ENTRY:
        $bookId = arg(2);
        $catalog = _makeCompleteEntry($bookId);
        break;*/

        default:
            __tryCachedOutput($cacheInterval, '_makeCatalogRoot', array());
        //            $catalog = _makeCatalogRoot();
    }

}

function __buildPath(array $elements)
{
    if (count($elements) == 0) {
        $path = '__empty__';
    } else {
        $path = '';
        foreach ($elements as $element) {
            $path .= (strlen($element) ? $element : '__empty__');
        }
    }

    return md5($path);
}

function __tryCachedAuthenticatedOutput($cacheHours, $functionName, $functionParams) {
    global $user;
    $userId = $user->uid;
    if (!$userId && !_authenticateUser()) {
        // not authenticated
        return;
    } else {
        __tryCachedOutput($cacheHours, $functionName, $functionParams);
    }
}

function _authenticateUser() {
    $userName = $_SERVER["PHP_AUTH_USER"];
    $userPassword = $_SERVER["PHP_AUTH_PW"];
    if ($userName && $userPassword) {
        $form_values['name'] = $userName;
        $form_values['pass'] = $userPassword;
        if (user_authenticate($form_values)) {
            return true; // authenticated
        }
    }
    ob_start();
    drupal_set_header('Status: 401 Unauthorized');
    drupal_set_header('HTTP/1.1 401 Unauthorized');
    drupal_set_header('WWW-Authenticate: Basic realm="Flibusta authentication"');
//    drupal_set_header('X-OPDS-Register: https://www.feedbooks.com/user/register');
//    drupal_set_header('X-Runtime: 2');
    print "HTTP Basic: Access denied.\n";
    ob_flush();
    return false;
}

function __tryCachedOutput($cacheHours, $functionName, $functionParams)
{

    if ($cacheHours == 0) { // do not use cache
        $catalog = call_user_func_array($functionName, $functionParams);
        ob_start();
        drupal_set_header('Content-Type: application/atom+xml;charset=utf-8');
        print '<?xml version="1.0" encoding="utf-8"?>';
        print "\n";
        print format_xml_elements($catalog);
        ob_flush();
        return;
    }

    global $user;
    $autenticatedUserPrefix = $user->uid ? 'auth/' : '';
    //    $autenticatedUserPrefix = $user->uid ? $user->uid . '/' : '';

    $cacheFile = "cache/$autenticatedUserPrefix$functionName" . __buildPath($functionParams);
    if ($fh = libOpenCacheFile($cacheFile, 3600 * $cacheHours)) { // cache expired, build new one
        try {
            $catalog = call_user_func_array($functionName, $functionParams);
            fwrite($fh, '<?xml version="1.0" encoding="utf-8"?>');
            fwrite($fh, "\n");
            fwrite($fh, format_xml_elements($catalog));
            fclose($fh);
        } catch (Exception $e) {
            Global $key;
            if ($key) sem_release($key);
            error_log('Create OPDS catalog failed for request ' . $cacheFile . 'with parameters ' . var_export($functionParams, true));
            return;
        }
    }
    ob_start();
    drupal_set_header('Content-Type: application/atom+xml;charset=utf-8');
    print libReadCacheFile($cacheFile);
    ob_flush();
}

function _makeCatalogRedirect() {
    $catalog = _createCatalog('tag:fb-redirect', 'flibusta.net catalog - update your link');
    $catalog->addLink('http://213.5.65.159/opds', 'self', 'application/atom+xml;profile=opds-catalog');

    $entry = new OPDSCatalogEntry();
    $entry->addItem('id', 'tag:root');
    $entry->addItem('title', 'http://213.5.65.159/opds - Сервер переехал.');
    $entry->addItem(_createContent('Новый адрес - http://213.5.65.159/opds. Пожалуйста, обновите ссылку на каталог'));
    $entry->addLink('http://213.5.65.159/opds', null, 'application/atom+xml;profile=opds-catalog');
    $catalog->addEntry($entry);

    return array($catalog->toArray());
}


function _makeCatalogRoot()
{
    $catalog = _createCatalog('tag:root', 'flibusta.net catalog');
    //    $catalog->addItem('icon', url(check_url(theme_get_setting('favicon'))));
    $catalog->addLink(OPDS_CATALOG_ROOT, 'self', 'application/atom+xml;profile=opds-catalog');


    $entry = new OPDSCatalogEntry();
    //    $entry->addLink(url(theme_get_setting('favicon'), array('absolute' => TRUE)), 'http://opds-spec.org/image/thumbnail', 'image/png');
    $entry->addItem('id', 'tag:root:new');
    $entry->addItem('title', 'Новинки');
    $entry->addItem(_createContent('Новые поступления за неделю'));
    $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_NEW, 'http://opds-spec.org/sort/new', 'application/atom+xml;profile=opds-catalog');
    $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_NEW, null, 'application/atom+xml;profile=opds-catalog');
    $catalog->addEntry($entry);

    $entry = new OPDSCatalogEntry();
    $entry->addItem('id', 'tag:root:authors');
    $entry->addItem('title', 'По авторам');
    $entry->addItem(_createContent('Поиск книг по авторам'));
    $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_AUTHORS_INDEX, null, 'application/atom+xml;profile=opds-catalog');
    $catalog->addEntry($entry);

    $entry = new OPDSCatalogEntry();
    $entry->addItem('id', 'tag:root:sequences');
    $entry->addItem('title', 'По сериям');
    $entry->addItem(_createContent('Поиск книг по сериям'));
    $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_SEQUENCES_INDEX, null, 'application/atom+xml;profile=opds-catalog');
    $catalog->addEntry($entry);

    $entry = new OPDSCatalogEntry();
    $entry->addItem('id', 'tag:root:genre');
    $entry->addItem('title', 'По жанрам');
    $entry->addItem(_createContent('Поиск книг по жанрам'));
    $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_GENRES, null, 'application/atom+xml;profile=opds-catalog');
    $catalog->addEntry($entry);

//    $entry = new OPDSCatalogEntry();
//    $entry->addItem('id', 'tag:root:shelf');
//    $entry->addItem('title', 'Моя полка');
//    $entry->addItem(_createContent('Отложенные книги (требуется логин)'));
//    $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_POLKA, null, 'application/atom+xml;profile=opds-catalog');
//    $catalog->addEntry($entry);

    return array($catalog->toArray());
}

function _makeShelvedBooksCatalog($enableConverters) {
    global $user;
    $userId = $user->uid;
    $catalogId = 'tag:shelf:books:' . $userId;
    $catalog = _createCatalog($catalogId, 'Отложенные книги');

    $shelfDAO = new PolkaDAO();
    $bookDAO = new BookDAO();
    $postponedBooks = $shelfDAO->getPostponedBooks($userId);

    foreach($postponedBooks as $postponedBook) {
        $book = $bookDAO->getBook($postponedBook->getBookId(), true);
        if (!$book) {
            continue;
        }
        $bookEntry = _createCompleteBookEntry($book, $enableConverters);
        $bookEntry->addItem('summary', $postponedBook->getComment());
        $catalog->addEntry($bookEntry);
    }

    return array($catalog->toArray());

}

function _makeGenresCatalog($meta = null)
{
    $catalogId = 'tag:root:genre' . ($meta == null ? '' : ":$meta");

    $catalog = _createCatalog($catalogId, 'Книги по жанрам');

    $genreDAO = new GenreDAO();
    if ($meta == null) {
        $genres = $genreDAO->findMetaGenre();
    } else {
        $genres = $genreDAO->findGenre($meta);
    }
    foreach ($genres as $genre) {
        $entry = new OPDSCatalogEntry();
        if ($meta == null) {
            $genreId = $genre->getMeta();
            $genreName = $genreId;
            $genreUrl = OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_GENRES . '/';
            $description = 'Книги в жанре ' . $genreName;
        } else {
            $genreId = $genre->getId();
            $genreName = $genre->getDescription();
            $genreUrl = OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_GENRES . '/' . $genre->getMeta() . '/';
            $description = __format_plural_rus('@count книга', '@count книги', '@count книг', $genre->getBooksNumber());
        }
        $entry->addItem('id', $catalogId . ':' . $genreId);
        $entry->addItem('title', $genreName);
        $entry->addItem(_createContent($description));
        $entry->addLink($genreUrl . $genreId, null, 'application/atom+xml;profile=opds-catalog');
        $catalog->addEntry($entry);
    }

    return array($catalog->toArray());

}


function _createCatalog($id, $title)
{
    $catalog = new OPDSCatalog();
    $catalog->addItem('id', $id);
    $catalog->addItem('title', $title);
    $catalog->addItem('updated', date(DateTime::ATOM));
    $catalog->addItem('icon', url('favicon.ico', array('absolute' => TRUE)));
    //    $catalog->addLink('http://feedbooks.com/opensearch.xml', 'search', 'application/opensearchdescription+xml');
    $catalog->addLink('opds-opensearch.xml', 'search', 'application/opensearchdescription+xml');
    $catalog->addLink(url(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_SEARCH,
                          array(
                               'query' => 'searchTerm={searchTerms}',
                               'absolute' => true
                          )),
                      'search',
                      'application/atom+xml', true);
    //     <link rel="search" title="Search Catalog" type="application/atom+xml" href="/munseys/op/search?&amp;search={searchTerms}"/>


    $catalog->addLink(OPDS_CATALOG_ROOT, 'start', 'application/atom+xml;profile=opds-catalog');

    return $catalog;
}

function _createContent($text)
{
    return array(
        'key' => 'content',
        'value' => $text,
        'attributes' => array('type' => 'text')
    );
}

function _createBookAuthor(Author $author)
{

    return array(
        'key' => 'author',
        'value' => array(
            'name' => _composeAuthorName($author),
            'uri' => url('a/' . $author->getId(), array('absolute' => true))
        )
    );
}

function _composeAuthorName(Author $author)
{
    $name = '';
    if ($author->getLastName()) $name .= $author->getLastName();
    if ($author->getFirstName()) $name .= ' ' . $author->getFirstName();
    if ($author->getMiddleName()) $name .= ' ' . $author->getMiddleName();
    return $name;
}


function _createCategory(Genre $genre)
{
    return array(
        'key' => 'category',
        'attributes' => array(
            'term' => $genre->getDescription(),
//            'term' => $genre->getId(),
            'label' => $genre->getDescription()
        )
    );
}

function _createAnnotation($annotation, $checkMarkup = true)
{
    return array(
        'key' => 'content',
        'value' => $checkMarkup ? check_markup($annotation) : $annotation,
        'attributes' => array('type' => 'text/html')
    );
}

function _makeBooksCatalogByGenre($genreId, $pageNumber, $enableConverters)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);

    $bookDAO = new BookDAO();
    $genreDAO = new GenreDAO();

    $genre = $genreDAO->getGenre($genreId);
    if (!$genre) {
        // invalid request
        return;
    }
    $books = $bookDAO->findBookByGenre($genreId, $pageNumber, $pageSize, true);

    $catalogId = 'tag:root:genre:' . "$genreId:$pageNumber";

    $catalog = _createCatalog($catalogId, 'Книги в жанре ' . $genre->getDescription());
    $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_GENRES . '/' . $genre->getMeta(), 'up', 'application/atom+xml;profile=opds-catalog');
    if (count($books) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_GENRES . '/' . $genre->getMeta() . '/' . $genreId . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }


    // partial catalog enries не работают, как минимум в FbReaderJ 0.7.17
    // придется делать full entry
    foreach ($books as $book) {
        $entry = _createCompleteBookEntry($book, $enableConverters);
        // add link to complete entry
        //        $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_BOOK_ENTRY . '/' . $book->getId(), 'alternate',
        //                        'application/atom+xml;type=entry;profile=opds-catalog');
        $catalog->addEntry($entry);
    }


    return array($catalog->toArray());
}


function _createCompleteBookEntry(Book $book, $enableConverters)
{
//    $enableConverters = variable_get('librusec_Convert', FALSE);

    $genreDAO = new GenreDAO();
    $authorDAO = new AuthorDAO();
    $sequenceDAO = new SequenceDAO();

    $entry = new OPDSCatalogEntry();
    $entry->addItem('id', 'tag:book:' . $book->getId());
    $bookTitle = $book->getTitle();
    if ($book->getTitle1()) {
        $bookTitle .= ' [' . $book->getTitle1() . ']';
    }
    $entry->addItem('title', $bookTitle);

    $authors = $authorDAO->findAuthorsByBook($book->getId());
    foreach ($authors as $author) {
        $entry->addItem(_createBookAuthor($author));
        $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_BOOKS_CATALOG . '/' . $author->getId(),
                        'related', 'application/atom+xml', false, 'Все книги автора ' . _composeAuthorName($author));

    }

    $genres = $genreDAO->findGenreByBook($book->getId());
    foreach ($genres as $bookGenre) {
        $entry->addItem(_createCategory($bookGenre));
    }

    if ($book->getLang()) {
        $entry->addItem('dc:language', $book->getLang());
    }

    $bookFormat = $book->getFormat();
    if ($bookFormat == 'mobi') {
        $compressFormat = 'x-mobipocket-ebook';
    } elseif ($bookFormat != 'fb2') {
        $compressFormat = $bookFormat;

        // если extension файла не совпадает с форматом книги, то считаем файл упакованным
        $bookDAO = new BookDAO();
        $fileName = $bookDAO->getBookFileName($book->getId());
        if ($fileName) {
            $pathInfo = pathinfo($fileName);
            if ($pathInfo['extension'] != $bookFormat) {
                $compressFormat = $bookFormat . '+'.$pathInfo['extension'];
            }
        }
    } else {
        $compressFormat = 'fb2+zip';
    }
    $entry->addItem('dc:format', $compressFormat);

    $bookDescription = '';
    if ($book->getAnnotation()) {
        $bookDescription .=  $book->getAnnotation() . '<br/>';
    }

    $translators = $authorDAO->findTranslatorsByBook($book->getId());
    if (count($translators) > 0) {
        $translatorNames = array();
        foreach ($translators as $translator) {
            array_push($translatorNames, _composeAuthorName($translator));
        }
        $bookDescription .= 'Перевод: ' . join(', ', $translatorNames) . '<br/>';

    }

    if ($book->getIssueYear()) {
        $bookDescription .= 'Год издания: ' . $book->getIssueYear() . '<br/>';
        $entry->addItem('dc:issued', $book->getIssueYear());
    }

    $bookDescription .= 'Формат: ' . $bookFormat . '<br/>';
    if ($book->getLang()) {
        $bookDescription .= 'Язык: ' . $book->getLang() . '<br/>';
    }

    if ($book->getSize()) {
        $bookSize = $book->getSize();
        $sizeUnit = 'B';
        if ($bookSize > 10240) {
            $bookSize = (integer)($bookSize/1024);
            $sizeUnit = 'Kb';
        }
        $bookDescription .= "Размер: $bookSize $sizeUnit<br/>";

    }
    if ($book->getDownloadsNumber()) {
        $bookDescription .= 'Скачиваний: ' . $book->getDownloadsNumber() . '<br/>';
    }

    $sequenceByBook = $sequenceDAO->findSequenceByBook($book->getId());
    if (count($sequenceByBook) > 0) {
        foreach ($sequenceByBook as $sequence) {
            $bookDescription .= "Серия: " . $sequence->getName();
            if ($sequence->getBooksInSequence()) {
                $bookDescription .= ' #' . $sequence->getBooksInSequence(); // getBooksInSequence заполняется номером книги в серии
            }
            $bookDescription .= '<br/>';
            $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_SEQENCE_BOOKS_CATALOG . '/' . $sequence->getId(), 'related', 'application/atom+xml', false,
                            'Все книги серии "' . $sequence->getName() . '"');
        }
    }

    $entry->addItem(_createAnnotation($bookDescription, false));

    $coverImage = $book->getCoverImage();
    if ($coverImage) {
        $coverImage = ltrim($coverImage, '/');
//        $imageInfo = getimagesize($coverImage);
        $imageInfo = true;
        if ($imageInfo) {
//            $imageType = image_type_to_mime_type($imageInfo[2]);
            $fileExtension = pathinfo($coverImage, PATHINFO_EXTENSION);
            if ($fileExtension == 'jpg') {
                $imageType = 'image/jpeg';
            } else {
                $imageType = 'image/'.$fileExtension;
            }
            $coverImage = DEBUG_SERVER_PREFIX .$coverImage;
            $entry->addLink($coverImage, 'http://opds-spec.org/image', $imageType);
            $entry->addLink($coverImage, 'x-stanza-cover-image', $imageType);
            $entry->addLink($coverImage, 'http://opds-spec.org/thumbnail', $imageType);
            $entry->addLink($coverImage, 'x-stanza-cover-image-thumbnail', $imageType);
        }
    }

    if ($enableConverters && $bookFormat == 'fb2') { // converters enabled
        global $libSupportedFormats;
        foreach ($libSupportedFormats as $fmt) {
            $convertedCompressionFormat =  $fmt == 'mobi' ? 'x-mobipocket-ebook' :  $fmt . '+zip';
            $entry->addLink(DEBUG_SERVER_PREFIX.'b/' . $book->getId() . '/' . $fmt,
                            'http://opds-spec.org/acquisition/open-access', "application/$convertedCompressionFormat");
        }
    } else {
        // original format only
        $entry->addLink(DEBUG_SERVER_PREFIX.'b/' . $book->getId() . '/download',
                        'http://opds-spec.org/acquisition/open-access', 'application/' . $compressFormat);
    }

    $entry->addLink(DEBUG_SERVER_PREFIX.'b/' . $book->getId(), 'alternate', 'text/html', false, 'Книга на сайте');


    return $entry;
}

function _createCompleteAuthorEntry(Author $author)
{
    $entry = new OPDSCatalogEntry();
    $entry->addItem('id', 'tag:author:' . $author->getId());
    $entry->addItem("title", _composeAuthorName($author));
    if ($author->getBooksNumber()) {
        $entry->addItem(_createContent(__format_plural_rus('@count книга', '@count книги', '@count книг', $author->getBooksNumber())));
    } else {
        $entry->addItem(_createContent("Список книг"));
    }
    $entry->addLink(implode('/', array(OPDS_CATALOG_ROOT, OPDS_AUTHOR_BOOKS_CATALOG, $author->getId())),
                    null, 'application/atom+xml;profile=opds-catalog');
    $authorDAO = new AuthorDAO();
    $annotation = $authorDAO->getAuthorAnnotation($author->getId());
    if ($annotation) {
        if (is_array($annotation->getAttachedFiles())) {
            foreach ($annotation->getAttachedFiles() as $fileId => $attachedFile) {
                if (strstr($attachedFile->filemime, 'image')) {
                    $entry->addLink($attachedFile->filepath, 'http://opds-spec.org/image', $attachedFile->filemime);
                    $entry->addLink($attachedFile->filepath, 'x-stanza-cover-image', $attachedFile->filemime);
                    $entry->addLink($attachedFile->filepath, 'http://opds-spec.org/image/thumbnail', $attachedFile->filemime);
                    $entry->addLink($attachedFile->filepath, 'x-stanza-cover-image-thumbnail', $attachedFile->filemime);
                    break;
                }
            }
        }
    }

    $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCES_CATALOG . '/' . $author->getId(),
                    'http://www.feedbooks.com/opds/facet', 'application/atom+xml;profile=opds-catalog', false, 'Книги автора по сериям');

    $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCELESS_BOOKS_CATALOG . '/' . $author->getId(),
                    'http://www.feedbooks.com/opds/facet', 'application/atom+xml;profile=opds-catalog', false, 'Книги автора вне серий');

    return $entry;
}

function _createCompleteSequenceEntry(Sequence $sequence)
{
    $entry = new OPDSCatalogEntry();
    $entry->addItem('id', 'tag:sequence:' . $sequence->getId());
    $entry->addItem("title", $sequence->getName());
    $entry->addItem(_createContent(__format_plural_rus('@count книга','@count книги','@count книг',$sequence->getBooksInSequence()). ' в серии'));
    $entry->addLink(implode('/', array(OPDS_CATALOG_ROOT, OPDS_SEQENCE_BOOKS_CATALOG, $sequence->getId())),
                    null, 'application/atom+xml;profile=opds-catalog');
    return $entry;
}

function __russian_first_sort($a, $b)
{
    if ($a == '') {
        if ($b == '') {
            return 0;
        }
        return -1;
    } else if ($b == '') {
        return 1;
    }


    $aa = unpack('N*', mb_convert_encoding(mb_strtoupper($a), 'UCS-4BE', 'UTF-8'));
    $ba = unpack('N*', mb_convert_encoding(mb_strtoupper($b), 'UCS-4BE', 'UTF-8'));
    $aaLength = count($aa);
    $baLength = count($ba);
    $len = min($aaLength, $baLength);
    for ($i = 1; $i <= $len; $i++) {
        $aaCode = $aa[$i];
        $baCode = $ba[$i];
        if ($aaCode == $baCode) {
            continue;
        }
        $aCyr = $aaCode >= 0x410 && $aaCode <= 0x42f;
        $bCyr = $baCode >= 0x410 && $baCode <= 0x42f;

        if ($aCyr) {
            if ($bCyr) {
                return $aaCode > $baCode ? 1 : -1;
            } else {
                return -1;
            }
        } else {
            if ($bCyr) {
                return 1;
            } else {
                return $aaCode > $baCode ? 1 : -1;
            }
        }
    }
    // all chars are same
    if ($aaLength == $baLength) {
        return 0;
    }
    return $aaLength > $baLength ? 1 : -1;
}

function _makeAuthorsIndex($namePrefix)
{
    $authorsCountLimit = variable_get('librusec_OPDSAuthorsPP', OPDS_AuthorsPP);

    $catalogId = 'tag:root:authors' . ($namePrefix == null ? '' : ":$namePrefix");
    if ($namePrefix == null) {
        $namePrefix = '';
    }

    $catalog = _createCatalog($catalogId, 'Книги по авторам');

    $authorDAO = new AuthorDAO();
    $authors = $authorDAO->groupAuthorsByName($namePrefix);
    uksort($authors, "__russian_first_sort");
    foreach ($authors as $prefix => $count) {
        if ($prefix != $namePrefix) {
            $entry = new OPDSCatalogEntry();
            $entry->addItem('id', 'tag:authors:' . $prefix);
            $entry->addItem("title", $prefix);
            $entry->addItem(_createContent(__format_plural_rus("@count автор на '$prefix'", "@count автора на '$prefix'", "@count авторов на '$prefix'", $count)));
            if ($count > $authorsCountLimit) {
                $entry->addLink(implode('/', array(OPDS_CATALOG_ROOT, OPDS_CATALOG_AUTHORS_INDEX, $prefix)),
                                null, 'application/atom+xml;profile=opds-catalog');
            } else {
                $entry->addLink(implode('/', array(OPDS_CATALOG_ROOT, OPDS_CATALOG_AUTHORS, $prefix)),
                                null, 'application/atom+xml;profile=opds-catalog');
            }
            $catalog->addEntry($entry);
        } else {
            $authorsByName = $authorDAO->findAuthorByName($prefix, 0, null, true); // авторы с точным соответствием по фамилии
            $bookDAO = new BookDAO();
            foreach ($authorsByName as $author) {
                /** @var $author Author */
                if ($author->getBooksNumber() === null) {
                    $author->setBooksNumber($bookDAO->countBookByAuthor($author->getId()));
                }
                if ($author->getBooksNumber() > 0) {
                    $catalog->addEntry(_createCompleteAuthorEntry($author));
                }
            }
        }
    }
    return array($catalog->toArray());
}

function _makeAuthorsCatalog($namePrefix = null, $pageNumber = null)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);

    $catalogId = 'tag:root:authors' . ($namePrefix == null ? '' : ":$namePrefix")
                 . ($pageNumber != null ? ":$pageNumber" : '');

    $catalog = _createCatalog($catalogId, 'Книги по авторам');


    $authorDAO = new AuthorDAO();
    $authors = $authorDAO->findAuthorByName($namePrefix, $pageNumber, $pageSize);


    if (count($authors) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_AUTHORS . '/' . $namePrefix . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    foreach ($authors as $author) {
        $catalog->addEntry(_createCompleteAuthorEntry($author));
    }


    return array($catalog->toArray());
}

function _makeBooksCatalogByAuthor($authorId, $pageNumber, $enableConverters, $disabeFeedTypeMix)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);

    $bookDAO = new BookDAO();
    $authorDAO = new AuthorDAO();

    $catalogId = "tag:author:$authorId:$pageNumber";

    $author = $authorDAO->getAuthor($authorId);
    if (!$author) {
        return null; // author not found
    }

    $authorName = _composeAuthorName($author);
    $catalog = _createCatalog($catalogId, 'Книги автора ' . $authorName);

    $books = $bookDAO->findBookByAuthor($authorId, $pageNumber, $pageSize, true);

    if (count($books) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_BOOKS_CATALOG . '/' . $authorId . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    if ($pageNumber == null || $pageNumber == 0) {
        //  create author bio entry
        $annotation = $authorDAO->getAuthorAnnotation($authorId);
        if ($annotation) {
            $entry = new OPDSCatalogEntry();
            $entry->addItem('id', 'tag:author:bio:' . $authorId);
            $entry->addItem('title', 'Об авторе');
            $text = check_markup($annotation->getAnnotation());


            $img = '';
            if (is_array($annotation->getAttachedFiles())) {
                foreach ($annotation->getAttachedFiles() as $fileId => $attachedFile) {
                    if (strstr($attachedFile->filemime, 'image')) {
                        $entry->addLink($attachedFile->filepath, 'http://opds-spec.org/image', $attachedFile->filemime);
                        $entry->addLink($attachedFile->filepath, 'x-stanza-cover-image', $attachedFile->filemime);
                        $entry->addLink($attachedFile->filepath, 'http://opds-spec.org/image/thumbnail', $attachedFile->filemime);
                        $entry->addLink($attachedFile->filepath, 'x-stanza-cover-image-thumbnail', $attachedFile->filemime);
                        break;
                    }
                }
                $index = 0;
                foreach ($annotation->getAttachedFiles() as $fileId => $attachedFile) {
                    if (!strstr($text, $attachedFile->filepath)) {
                        if (strstr($text, "$$$index$$")) {
                            $text = str_replace("$$$index$$", '<img src="' . url($attachedFile->filepath, array('absolute' => TRUE)) . '" align=left style="border:5px solid #ededed; margin: 12px;">', $text);
                        } else {
                            if ($img) {
                                $img .= " &nbsp ";
                            }
                            $img .= '<img src="' . url($attachedFile->filepath, array('absolute' => TRUE)) . '" align=left style="border:5px solid #ededed; margin: 12px;">';
                        }
                    }
                    $index++;
                }
            }

            $entry->addItem(_createAnnotation($img . $text, false));
            $entry->addLink("a/$authorId", 'alternate', 'text/html', false, 'Страница автора на сайте');
            $entry->addLink("a/$authorId", 'http://opds-spec.org/acquisition', 'text/html', false, 'Страница автора на сайте');

            $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCES_CATALOG . '/' . $authorId,
                            'http://www.feedbooks.com/opds/facet', 'application/atom+xml;profile=opds-catalog', false, 'Книги автора по сериям');

            $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCELESS_BOOKS_CATALOG . '/' . $authorId,
                            'http://www.feedbooks.com/opds/facet', 'application/atom+xml;profile=opds-catalog', false, 'Книги автора вне серий');

            $catalog->addEntry($entry);
        }

        // additional navigatopn links
        if (!$disabeFeedTypeMix) {
            $entry = new OPDSCatalogEntry();
            $entry->addItem('id', "tag:author:$authorId:sequences");
            $entry->addItem('title', 'Книги по сериям');
            $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCES_CATALOG . '/' . $authorId,
                            null, 'application/atom+xml;profile=opds-catalog');
            $catalog->addEntry($entry);

            $entry = new OPDSCatalogEntry();
            $entry->addItem('id', "tag:author:$authorId:sequenceless");
            $entry->addItem('title', 'Книги вне серий');
            $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCELESS_BOOKS_CATALOG . '/' . $authorId,
                            null, 'application/atom+xml;profile=opds-catalog');
            $catalog->addEntry($entry);
        }
    }

    foreach ($books as $book) {
        $entry = _createCompleteBookEntry($book, $enableConverters);
        $catalog->addEntry($entry);
    }
    return array($catalog->toArray());

}

function _makeNewCatalog($pageNumber = 0, $type = 'books', $typeId = null, $enableConverters)
{

    $searchInterval = OPDS_NEW_BOOKS_SEARCH_INTERVAL; // days


    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $bookDAO = new BookDAO();

    $catalogId = "tag:search:new:book:$pageNumber";
    $currentTime = time();
    $endDate = date('d.m.Y', $currentTime);

    $beginDate = date('d.m.Y', $currentTime - $searchInterval * 24 * 3600);; //$date->sub(new DateInterval('P'.$searchInterval.'D'))->format('d.m.Y');
    $catalog = _createCatalog($catalogId, "Новинки с $beginDate по $endDate");

    $books = array();
    switch ($type) {
        case OPDS_CATALOG_NEW:
            $books = $bookDAO->findBookByCreationDate($searchInterval, $pageNumber, $pageSize, true);
            break;
        case OPDS_CATALOG_NEW_GENRES:
            $books = $bookDAO->findBookByGenre($typeId, $pageNumber, $pageSize, true, $searchInterval);
            break;
        case OPDS_CATALOG_NEW_AUTHORS:
            $books = $bookDAO->findBookByAuthor($typeId, $pageNumber, $pageSize, true, $searchInterval);
            break;
        case OPDS_CATALOG_NEW_SEQUENCES:
            $books = $bookDAO->findBookBySequence($typeId, $pageNumber, $pageSize, true, $searchInterval);
            break;
        default:
            $entry = new OPDSCatalogEntry();
            $entry->addItem('id', 'tag:search:new:books');
            $entry->addItem('title', 'Все новинки');
            $newBooksNumber = $bookDAO->countBookByCreationDate($searchInterval);
            $entry->addItem('content', __format_plural_rus('@count новая книга', '@count новые книги', '@count новых книг', $newBooksNumber));
            $entry->addLink(OPDS_CATALOG_ROOT .'/'.OPDS_CATALOG_NEW.'/0/'.OPDS_CATALOG_NEW, null, 'application/atom+xml;profile=opds-catalog');
            $catalog->addEntry($entry);

            $entry = new OPDSCatalogEntry();
            $entry->addItem('id', 'tag:search:new:genres');
            $entry->addItem('title', 'По жанрам');
            $entry->addItem('content', 'Новые книги по жанрам');
            $entry->addLink(OPDS_CATALOG_ROOT .'/'.OPDS_CATALOG_NEW_GENRES, null, 'application/atom+xml;profile=opds-catalog');
            $catalog->addEntry($entry);

            $entry = new OPDSCatalogEntry();
            $entry->addItem('id', 'tag:search:new:authors');
            $entry->addItem('title', 'По авторам');
            $entry->addItem('content', 'Новые книги по авторам');
            $entry->addLink(OPDS_CATALOG_ROOT .'/'.OPDS_CATALOG_NEW_AUTHORS, null, 'application/atom+xml;profile=opds-catalog');
            $catalog->addEntry($entry);

            $entry = new OPDSCatalogEntry();
            $entry->addItem('id', 'tag:search:new:sequences');
            $entry->addItem('title', 'По сериям');
            $entry->addItem('content', 'Новые книги по сериям');
            $entry->addLink(OPDS_CATALOG_ROOT .'/'.OPDS_CATALOG_NEW_SEQUENCES, null, 'application/atom+xml;profile=opds-catalog');
            $catalog->addEntry($entry);


    }

    if (count($books) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_NEW . '/' . ($pageNumber + 1) . '/' . $type .'/' . $typeId,
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    foreach ($books as $book) {
        $entry = _createCompleteBookEntry($book, $enableConverters);
        $catalog->addEntry($entry);
    }

    return array($catalog->toArray());

}

function __format_plural_rus($singular, $plural1, $plural2, $count) {
    if ($count >= 10 && $count <= 19) {
        return str_replace('@count', $count, $plural2);
    }
    $cnt = $count % 10;
    if ($cnt == 1) {
        return str_replace('@count', $count, $singular);
    }
    if ($cnt > 1 && $cnt < 5) {
        return str_replace('@count', $count, $plural1);
    }

    return str_replace('@count', $count, $plural2);
}

function _makeNewGenresCatalog($pageNumber = 0)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $catalogId = "tag:search:new:genres:$pageNumber";
    $catalog = _createCatalog($catalogId, 'Новинки по жанрам');
    $genreDAO = new GenreDAO();
    $genres = $genreDAO->findGenresByBookCreationDate(OPDS_NEW_BOOKS_SEARCH_INTERVAL, $pageNumber, $pageSize);
    if (count($genres) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_NEW_GENRES . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    $genreUrl = OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_NEW .'/0/'.OPDS_CATALOG_NEW_GENRES.'/';
    foreach ($genres as $genre) {
        $entry = new OPDSCatalogEntry();
        $genreId = $genre->getId();
        $genreName = $genre->getDescription();

        $entry->addItem('id', $catalogId . ':' . $genreId);
        $entry->addItem('title', $genreName);
        $entry->addItem(_createContent(__format_plural_rus('@count новая книга', '@count новые книги', '@count новых книг', $genre->getBooksNumber())));
        $entry->addLink($genreUrl . $genreId, null, 'application/atom+xml;profile=opds-catalog');
        $catalog->addEntry($entry);

    }


    return array($catalog->toArray());

}
function _makeNewAuthorsCatalog($pageNumber = 0)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $catalogId = "tag:search:new:authors:$pageNumber";
    $catalog = _createCatalog($catalogId, 'Новинки по авторам');
    $dao = new AuthorDAO();
    $authors = $dao->findAuthorsByBookCreationDate(OPDS_NEW_BOOKS_SEARCH_INTERVAL, $pageNumber, $pageSize);
    if (count($authors) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_NEW_AUTHORS . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    $url = OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_NEW .'/0/'.OPDS_CATALOG_NEW_AUTHORS.'/';
    foreach ($authors as $author) {
        $entry = new OPDSCatalogEntry();
        $id = $author->getId();

        $entry->addItem('id', "tag:search:new:author:$id");
        $entry->addItem("title", _composeAuthorName($author));
        $entry->addItem(_createContent(__format_plural_rus('@count новая книга', '@count новые книги', '@count новых книг', $author->getBooksNumber())));
        $entry->addLink($url . $id, null, 'application/atom+xml;profile=opds-catalog');
        $catalog->addEntry($entry);

    }


    return array($catalog->toArray());

}
function _makeNewSequencesCatalog($pageNumber = 0)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $catalogId = "tag:search:new:sequences:$pageNumber";
    $catalog = _createCatalog($catalogId, 'Новинки по сериям');
    $dao = new SequenceDAO();
    $sequences = $dao->findSequencesByBookCreationDate(OPDS_NEW_BOOKS_SEARCH_INTERVAL, $pageNumber, $pageSize);
    if (count($sequences) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_NEW_SEQUENCES . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    $url = OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_NEW .'/0/'.OPDS_CATALOG_NEW_SEQUENCES.'/';
    foreach ($sequences as $sequence) {
        $entry = new OPDSCatalogEntry();
        $id = $sequence->getId();

        $entry->addItem('id', "tag:search:new:sequence:$id");
        $entry->addItem("title", $sequence->getName());
        $entry->addItem(_createContent(__format_plural_rus('@count новая книга', '@count новые книги', '@count новых книг', $sequence->getBooksInSequence())));
        $entry->addLink($url . $id, null, 'application/atom+xml;profile=opds-catalog');
        $catalog->addEntry($entry);

    }


    return array($catalog->toArray());

}


function _createSearchUrl($paramsArray)
{
    return url(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_SEARCH,
               array('absolute' => TRUE,
                    'query' => $paramsArray
               )
    );
}

function _makeCatalogBySearch($searchTerm, $searchType, $pageNumber, $enableConverters)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $catalogId = "tag:search:$searchType:$searchTerm:$pageNumber";

    $catalog = _createCatalog($catalogId, 'Результат поиска');


    if (!$searchType) {
        $entry = new OPDSCatalogEntry();
        $entry->addItem('id', 'tag:search:author');
        $entry->addItem("title", 'Поиск авторов');
        $entry->addItem(_createContent('Поиск авторов по фамилии'));

        $searchUrl = _createSearchUrl(array('searchType' => OPDS_CATALOG_SEARCH_AUTHORS, 'searchTerm' => $searchTerm));

        $entry->addLink($searchUrl,
                        null, 'application/atom+xml;profile=opds-catalog', true);
        $catalog->addEntry($entry);

        $entry = new OPDSCatalogEntry();
        $entry->addItem('id', 'tag:search:title');
        $entry->addItem("title", 'Поиск книг');
        $entry->addItem(_createContent('Поиск книг по названию'));
        $searchUrl = _createSearchUrl(array('searchType' => OPDS_CATALOG_SEARCH_BOOKS, 'searchTerm' => $searchTerm));

        $entry->addLink($searchUrl,
                        null, 'application/atom+xml;profile=opds-catalog', true);
        $catalog->addEntry($entry);

    } else {
        $searchUrl = _createSearchUrl(array('searchTerm' => $searchTerm));
        $catalog->addLink($searchUrl,
                          'up', 'application/atom+xml;profile=opds-catalog', true);

        if ($searchType == OPDS_CATALOG_SEARCH_AUTHORS) {

            $authorDAO = new AuthorDAO();
            $authors = $authorDAO->findAuthorByName($searchTerm, $pageNumber, $pageSize);

            if (count($authors) == $pageSize) {
                $searchUrl = _createSearchUrl(array('searchType' => $searchType, 'searchTerm' => $searchTerm, 'pageNumber' => ($pageNumber + 1)));
                $catalog->addLink($searchUrl,
                                  'next', 'application/atom+xml;profile=opds-catalog', true);
            }

            $bookDAO = new BookDAO();
            foreach ($authors as $author) {
                /** @var $author Author */
                if ($author->getBooksNumber() === null) {
                    $author->setBooksNumber($bookDAO->countBookByAuthor($author->getId()));
                }
                if ($author->getBooksNumber() > 0) {
                    $catalog->addEntry(_createCompleteAuthorEntry($author));
                }
            }
        }

        if ($searchType == OPDS_CATALOG_SEARCH_BOOKS) {
            $catalog = _createCatalogBySearchBooks($catalog, $searchTerm, $pageNumber, $pageSize, $enableConverters);
        }
    }

    return array($catalog->toArray());
}

function _createCatalogBySearchBooks(OPDSCatalog $catalog, $searchTerm, $pageNumber, $pageSize, $enableConverters) {
    $bookDAO = new BookDAO();
    $books = $bookDAO->findBookByName($searchTerm, $pageNumber, $pageSize, true);

    if (count($books) == $pageSize) {
        $searchUrl = _createSearchUrl(array('searchType' => OPDS_CATALOG_SEARCH_BOOKS, 'searchTerm' => $searchTerm, 'pageNumber' => ($pageNumber + 1)));
        $catalog->addLink($searchUrl,
                          'next', 'application/atom+xml;profile=opds-catalog', true);
    }
    foreach ($books as $book) {
        $entry = _createCompleteBookEntry($book, $enableConverters);
        $catalog->addEntry($entry);
    }
    return $catalog;
}

function _makeCatalogBySearchAll($searchTerm, $pageNumber, $enableConverters)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $catalogId = "tag:searchall:$searchTerm:$pageNumber";

    $catalog = _createCatalog($catalogId, 'Результат поиска книг');


    $bookDAO = new BookDAO();
    $booksCount = $bookDAO->countBookByName($searchTerm);

    $catalog = _createCatalogBySearchBooks($catalog, $searchTerm, $pageNumber, $pageSize, $enableConverters);

    $catalog->addItem('os:totalResults', $booksCount);
    $catalog->addItem('os:startIndex', $pageSize * $pageNumber);
    $catalog->addItem('os:itemsPerPage', $pageSize);

    return array($catalog->toArray());
}


function _makeSequencesCatalogByAuthor($authorId, $pageNumber)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $catalogId = "tag:author:$authorId:sequences:$pageNumber";

    $authorDAO = new AuthorDAO();
    $author = $authorDAO->getAuthor($authorId);
    if (!$author) {
        return null;
    }

    $catalog = _createCatalog($catalogId, 'Книжные серии ' . _composeAuthorName($author));

    $sequenceDAO = new SequenceDAO();

    $sequences = $sequenceDAO->findSequenceByAuthor($authorId, $pageNumber, $pageSize);

    if (count($sequences) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCES_CATALOG . '/' . $authorId . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }


    /** var $sequence Sequence */
    foreach ($sequences as $sequence) {
        $entry = new OPDSCatalogEntry();
        $entry->addItem('id', "tag:author:$authorId:sequence:" . $sequence->getId());
        $entry->addItem("title", $sequence->getName());
        $entry->addItem(_createContent(__format_plural_rus('@count книга','@count книги','@count книг',$sequence->getBooksInSequence()). ' в серии'));
        $entry->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCE_BOOKS_CATALOG . '/' . $authorId . '/' . $sequence->getId(),
                        null, 'application/atom+xml;profile=opds-catalog');
        $catalog->addEntry($entry);
    }
    return array($catalog->toArray());
}

function _makeSequenceBooksCatalogByAuthor($authorId, $sequenceId, $pageNumber, $enableConverters)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $catalogId = "tag:author:$authorId:sequence:$sequenceId:$pageNumber";

    $sequenceDAO = new SequenceDAO();
    $sequence = $sequenceDAO->getSequence($sequenceId);
    if (!$sequence) {
        return null;
    }

    $catalog = _createCatalog($catalogId, 'Книги в серии ' . $sequence->getName());

    $bookDAO = new BookDAO();

    $books = $bookDAO->findBookByAuthorSequence($authorId, $sequenceId, $pageNumber, $pageSize, true);

    if (count($books) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCE_BOOKS_CATALOG . '/' . $authorId . '/' . $sequenceId . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    foreach ($books as $book) {
        $entry = _createCompleteBookEntry($book, $enableConverters);
        $catalog->addEntry($entry);
    }
    return array($catalog->toArray());

}

function _makeSequencelessBooksCatalogByAuthor($authorId, $pageNumber, $enableConverters)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $catalogId = "tag:author:$authorId:sequenceless:$pageNumber";

    $catalog = _createCatalog($catalogId, 'Книги без серий');

    $bookDAO = new BookDAO();

    $books = $bookDAO->findBookByAuthorWithoutSequence($authorId, $pageNumber, $pageSize, true);

    if (count($books) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_AUTHOR_SEQENCELESS_BOOKS_CATALOG . '/' . $authorId . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    foreach ($books as $book) {
        $entry = _createCompleteBookEntry($book, $enableConverters);
        $catalog->addEntry($entry);
    }
    return array($catalog->toArray());

}

function _makeSequenceBooksCatalog($sequenceId, $pageNumber, $enableConverters)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);
    $catalogId = "tag:sequence:$sequenceId:$pageNumber";

    $sequenceDAO = new SequenceDAO();
    $sequence = $sequenceDAO->getSequence($sequenceId);
    if (!$sequence) {
        return;
    }

    $catalog = _createCatalog($catalogId, 'Книги в серии ' . $sequence->getName());

    $bookDAO = new BookDAO();

    $books = $bookDAO->findBookBySequence($sequenceId, $pageNumber, $pageSize, true);

    if (count($books) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_SEQENCE_BOOKS_CATALOG . '/' . $sequenceId . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    foreach ($books as $book) {
        $entry = _createCompleteBookEntry($book, $enableConverters);
        $catalog->addEntry($entry);
    }
    return array($catalog->toArray());

}


function _makeSequencesIndex($namePrefix)
{
    $authorsCountLimit = variable_get('librusec_OPDSAuthorsPP', OPDS_AuthorsPP);

    $catalogId = 'tag:root:sequences' . ($namePrefix == null ? '' : ":$namePrefix");
    if ($namePrefix == null) {
        $namePrefix = '';
    }

    $catalog = _createCatalog($catalogId, 'Книги по сериям');

    $sequenceDAO = new SequenceDAO();
    $seqences = $sequenceDAO->groupSequencesByName($namePrefix);
    uksort($seqences, "__russian_first_sort");
    foreach ($seqences as $prefix => $count) {
        if ($prefix != $namePrefix) {
            $entry = new OPDSCatalogEntry();
            $entry->addItem('id', 'tag:sequences:' . $prefix);
            $entry->addItem("title", $prefix);
            $entry->addItem(_createContent(__format_plural_rus('@count серия на', '@count серии на', '@count серий на', $count)." '$prefix'"));
            if ($count > $authorsCountLimit) {
                $entry->addLink(implode('/', array(OPDS_CATALOG_ROOT, OPDS_CATALOG_SEQUENCES_INDEX, $prefix)),
                                null, 'application/atom+xml;profile=opds-catalog');
            } else {
                $entry->addLink(implode('/', array(OPDS_CATALOG_ROOT, OPDS_CATALOG_SEQUENCES, $prefix)),
                                null, 'application/atom+xml;profile=opds-catalog');
            }
            $catalog->addEntry($entry);
        } else {
            $sequencesByName = $sequenceDAO->findSequenceByName($prefix, 0, null, true); // серии с точным соответствием по названию
            foreach ($sequencesByName as $sequence) {
                $catalog->addEntry(_createCompleteSequenceEntry($sequence));
            }
        }
    }
    return array($catalog->toArray());
}


function _makeSequencesCatalog($namePrefix = null, $pageNumber = null)
{
    $pageSize = variable_get('librusec_OPDSBooksPP', OPDS_BooksPP);

    $catalogId = 'tag:root:sequences' . ($namePrefix == null ? '' : ":$namePrefix")
                 . ($pageNumber != null ? ":$pageNumber" : '');

    $catalog = _createCatalog($catalogId, 'Книги по сериям');


    $sequenceDAO = new SequenceDAO();
    $sequences = $sequenceDAO->findSequenceByName($namePrefix, $pageNumber, $pageSize);


    if (count($sequences) == $pageSize) {
        $catalog->addLink(OPDS_CATALOG_ROOT . '/' . OPDS_CATALOG_SEQUENCES . '/' . $namePrefix . '/' . ($pageNumber + 1),
                          'next', 'application/atom+xml;profile=opds-catalog');
    }

    foreach ($sequences as $sequence) {
        $catalog->addEntry(_createCompleteSequenceEntry($sequence));
    }


    return array($catalog->toArray());
}
