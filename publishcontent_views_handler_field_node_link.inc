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

    if (!user_access('un/publish '. check_plain($node->type) .' content') &&
        !user_access('un/publish *all* content')) {
      return;
    }

    return l(t($node->status ? 'Unpublish' : 'Publish'),
             "node/$node->nid/". ($node->status ? 'unpublish' : 'publish'),
             array('query' => drupal_get_destination()));
  }
}
