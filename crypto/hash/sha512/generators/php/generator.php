
<?php

function random_positive_int() {
    if (($fp = fopen('/dev/urandom', 'rb')) !== FALSE) {
        $buf = '';
        do {
            $buf .= fread($fp, PHP_INT_SIZE);
        } while (strlen($buf) < PHP_INT_SIZE);
        fclose($fp);
    } else {
        other_methods();
    }
    $val = 0;
    $i = strlen($buf);
    do {
        $i--;
        $val <<= 8;
        $val |= ord($buf[$i]);
    } while ($i != 0);

    return $val & PHP_INT_MAX;
}

function random_uniform($min, $max) {
    $range = $max - $min;
    if ($range < 2) {
        return $min;
    }
    $rem = (PHP_INT_MAX - $range + 1) % $range;
    do {
        $val = random_positive_int();
    } while ($val < $rem);

    return $min + $val % $range;
}

function random_buf($len) {
    $buf = '';
    while ($len-- > 0) {
        $buf .= chr(random_positive_int() & 0xff);
    }
    return $buf;
}

function generate() {
    $len = random_uniform(0, MAX_MESSAGE_LENGTH + 1);
    $message = random_buf($len);
    $out_hex = hash('sha512', $message, FALSE);
    print bin2hex($message) . "\t" . $out_hex . "\n";
}

define('MAX_MESSAGE_LENGTH', 256);

if (empty($argv[1])) {
    die();
}
$count = intval($argv[1]);

while ($count-- > 0) {
    generate();
}
