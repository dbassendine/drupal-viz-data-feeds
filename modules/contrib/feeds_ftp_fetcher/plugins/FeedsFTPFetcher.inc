<?php
/**
 * @file
 * Feeds FTP Fetcher classses and functions.
 */

/**
 * Definition of the import batch object created on the fetching stage by
 * FeedsFTPFetcher.
 */
class FeedsFTPBatch extends FeedsFetcherResult {
  protected $server;
  protected $directory;
  protected $filename;
  protected $username;
  protected $password;
  protected $port;
  protected $file_path;

  /**
   * Constructor.
   */
  public function __construct($server, $directory, $filename, $username, $password, $port, $feed_nid) {
    $this->server = $server;
    $this->directory = $directory;
    $this->filename = $filename;
    $this->username = $username;
    $this->password = $password;
    $this->port = $port;
    parent::__construct('', $feed_nid);
  }

  /**
   * Implements FeedsFetcherResult::getRaw().
   */
  public function getRaw() {

    $connect = feeds_ftp_fetcher_connect($this->server, $this->username, $this->password, $this->port);

    if (!$connect) {
      throw new Exception(t('Failed to connect to ftp server: !server', array('!server' => $this->server)));
    }

    if (!feeds_ftp_fetcher_chdir($connect, $this->directory)) {
      throw new Exception(t('Failed to change FTP directory'));
    }

    $temp_file = feeds_ftp_fetcher_download($connect, $this->filename);
    if (!$temp_file) {
      throw new Exception(t('Failed to retrieve %filename from remote directory %directory', array(
        '%directory' => $this->directory,
        '%filename' => $this->filename,
      )));
    }
    return feeds_ftp_fetcher_get_data($temp_file);
  }
}

/**
 * Fetches data via FTP.
 */
class FeedsFTPFetcher extends FeedsFetcher {

  /**
   * Implements FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {

    $source_config = $source->getConfigFor($this);
    $ftp_password = ($this->config['password_field'] == 'config') ? $this->config['password'] : $source_config['ftp']['password'];

    return new FeedsFTPBatch(
      $this->config['server'],
      $this->config['directory'],
      $this->config['filename'],
      $this->config['username'],
      $ftp_password,
      $this->config['port'],
      $source->feed_nid
    );
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'server' => '',
      'port' => 21,
      'directory' => '/',
      'filename' => '',
      'username' => '',
      'password' => '',
      'password_field' => 'config',
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {

    $form = array();

    $form['password_field'] = array(
      '#title' => t('Where to provide password field'),
      '#type' => 'select',
      '#default_value' => $this->config['password_field'],
      '#options' => array('config' => t('Config page'), 'source' => t('Source form')),
    );

    $form['server'] = array(
      '#type' => 'textfield',
      '#title' => t('Server'),
      '#description' => t("Enter a server hostname. Do not include 'ftp://' prefix."),
      '#default_value' => $this->config['server'],
      '#maxlength' => NULL,
      '#required' => TRUE,
    );

    $form['port'] = array(
      '#type' => 'textfield',
      '#title' => t('Port'),
      '#description' => t('Enter a port to connect on.'),
      '#default_value' => $this->config['port'],
      '#maxlength' => NULL,
      '#required' => TRUE,
    );

    $form['directory'] = array(
      '#type' => 'textfield',
      '#title' => t('Directory'),
      '#description' => t("The directory on the FTP server. E.g., '/public_html'"),
      '#default_value' => $this->config['directory'],
      '#maxlength' => NULL,
      '#required' => TRUE,
    );

    $form['filename'] = array(
      '#type' => 'textfield',
      '#title' => t('Filename'),
      '#description' => t('The filename in the directory on the FTP server.'),
      '#default_value' => $this->config['filename'],
      '#maxlength' => NULL,
      '#required' => TRUE,
    );

    $form['username'] = array(
      '#type' => 'textfield',
      '#title' => t('Username'),
      '#description' => t('The username used to connect to the FTP server.'),
      '#default_value' => $this->config['username'],
      '#maxlength' => NULL,
      '#required' => TRUE,
    );

    $form['password'] = array(
      '#type' => 'password',
      '#title' => t('Password'),
      '#description' => t('The password used to connect to the FTP server.'),
      '#default_value' => '',
      '#maxlength' => NULL,
      '#required' => FALSE,
      '#states' => array(
        'visible' => array(
          ':input[name="password_field"]' => array('value' => 'config'),
        ),
      ),
    );
    return $form;
  }

  /**
   * Source form.
   */
  public function sourceForm($source_config) {
    $form = array();
    $form['ftp'] = array(
      '#title' => t('Ftp settings'),
      '#type' => 'fieldset',
      '#collapsed' => FALSE,
      '#collapsible' => FALSE,
    );

    $text = t('The source file for this import/update process is placed on ftp server. You have to provide some authentication data to access the file.');
    if ($this->config['server'] && $this->config['directory'] && $this->config['filename'] && $this->config['username']) {
      $text = t('Ftp server: %server, port: %port, directory: %dir, file: %file.',
        array(
          '%server' => $this->config['server'],
          '%port' => $this->config['port'],
          '%dir' => $this->config['directory'],
          '%file' => $this->config['filename'],
        ));

      if ($this->config['password_field'] == 'source') {
        $text .= '<br />' . t('Please provide FTP password here.');
      }
    }

    $form['ftp']['info'] = array('#markup' => $text);

    if ($this->config['password_field'] == 'source') {
      $form['ftp']['password'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#description' => t('The password used to connect to the FTP server.'),
        '#default_value' => '',
        '#maxlength' => NULL,
        '#required' => TRUE,
      );
    }
    return $form;
  }
}

function feeds_ftp_fetcher_connect($server, $username, $password, $port) {
  if ($connect = ftp_connect($server, $port)) {
    ftp_login($connect, $username, $password);
    ftp_pasv($connect, TRUE);
    return $connect;
  }
  return FALSE;
}

function feeds_ftp_fetcher_chdir($connect, $directory) {
  return @ftp_chdir($connect, $directory);
}

function feeds_ftp_fetcher_download($connect, $file) {
  $result = FALSE;
  $temp_file = file_create_filename($file, file_directory_temp());
  $fp = @fopen($temp_file, 'w');
  if (@ftp_fget($connect, $fp, $file, FTP_BINARY)) {
    $result = $temp_file;
  }
  @fclose($fp);
  return $result;
}

function feeds_ftp_fetcher_get_data($temp_file) {
  $data = '';
  if ($fp = @fopen($temp_file, 'rb')) {
    while (!feof($fp)) {
      $data .= fread($fp, 4096);
    }
    @fclose($fp);
  }
  return $data;
}
