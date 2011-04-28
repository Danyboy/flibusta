<?php

abstract class AbstractDAO {
    /**
     * Ограничитель для select statement (только для mysql)
     * @param int $pageNo
     * @param  $pageSize
     * @return string - "limit n1, n2" если указан pageSize или пустая строка
     */
    protected function makePagingLimit($pageNo = 0, $pageSize = null) {
        if ($pageSize) {
            $from = $pageNo * $pageSize;
            return " limit $from, $pageSize";
        } else {
            return '';
        }
    }



    protected function getLanguageRestriction($fieldName = 'Lang', $condition = 'and') {
        global $user;
        if ($user->uid) {
            return ''; // no restrictions for registered users
        }
        $ShowEN =  variable_get('librusec_ShowEN', '');
        $ShowGUS = variable_get('librusec_ShowGUS', '');

        if ($ShowGUS) {
            if (!$ShowEN) {
                return " $condition $fieldName in ('ru', 'be', 'uk', 'kk') ";
            } else {
                return '';
            }
        } else {
            if (!$ShowEN) {
                return " $condition $fieldName = 'ru' ";
            } else {
                return " $condition $fieldName not in ('ru', 'be', 'uk', 'kk') ";
            }
        }
    }

}
