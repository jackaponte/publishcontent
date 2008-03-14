PUBLISH CONTENT MODULE

This module adds another level to the access control of nodes with an "publish nodetype content" permission for each node type available to the system in addition to create, edit own, and edit content permissions. By enabling the "publish nodetype content" permission on a nodetype you can give a role the ability to view, edit, and publish unpublished nodes without being the node creator or having "administer nodes" permissions.

INSTALLATION

Put the module in your drupal modules directory and enable it in admin/modules.

If you are upgrading, be sure to run update.php as several changes are
required. This attempts to migrate your previous settings to the new setup in
drupal 5. I would strongly recommend backing up your database before installing
this module.

IMPORTANT

This module does not disable or override any other permission settings. It is simply another layer of granularity. This is not a replacement for the "edit (own) nodetype content" permission. This does not give the role access to delete nodes... you still will need "administer nodes" permission to do so!