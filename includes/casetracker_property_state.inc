<?php

/**
* Case meta-data handler for the state/realm system.
*/
class casetracker_property_state {
  function set($p) {
    $this->property = $p;
  }
  
  function setting_form(&$form) {
    $form['realm'] = array(
      '#type' => 'select',
      '#title' => t('Realm'),
      '#options' => casetracker_realm_list(),
      '#default_value' => $this->property->realm,
    );
    // TODO default value via AJAX
    $form['default_state'] = array(
      '#type' => 'select',
      '#title' => t('Default value'),
      '#options' => casetracker_realm_load($this->property->realm),
      '#default_value' => $this->property->default_state,
    );
  }

  function option_form(&$form, $node) {
    $form[$this->property->id] = array(
      '#type' => 'select',
      '#title' => $this->property->name,
      '#options' => casetracker_realm_load($this->property->realm),
      '#default_value' => isset($node->casetracker->{$this->property->id}) ? $node->casetracker->{$this->property->id} : null,
    );
  }

  /**
   * 
   */
  function display($info) {
    $state = casetracker_state_load($info[$this->property->id], $this->property->realm);
    return '<span class="' . $this->property->realm. '">' . $this->property->name . ': <strong>'. $state->title . '</strong></span>';
  }
}
