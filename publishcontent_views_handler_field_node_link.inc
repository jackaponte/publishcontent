<?php
// $Id$

/**
 * Field handler to present a link node publish.
 */
class publishcontent_views_handler_field_node_link extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['type'] = 'type';
    $this->additional_fields['status'] = 'status';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    // ensure user has access to edit this node.
    $node = new stdClass();
    $node->nid = $values->{$this->aliases['nid']};
    $node->type = $values->{$this->aliases['type']};
    $node->status = $values->{$this->aliases['status']};

    $options = array('query' => drupal_get_destination());
    if ($node->status && _publishcontent_unpublish_access($node))
      return l(t('Unpublish'), "node/$node->nid/unpublish", $options);

    if (!$node->status && _publishcontent_publish_access($node))
      return l(t('Publish'), "node/$node->nid/publish", $options);
  }
}
