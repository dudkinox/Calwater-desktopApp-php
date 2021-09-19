<?php

use Twig\Environment;
use Twig\Error\LoaderError;
use Twig\Error\RuntimeError;
use Twig\Extension\SandboxExtension;
use Twig\Markup;
use Twig\Sandbox\SecurityError;
use Twig\Sandbox\SecurityNotAllowedTagError;
use Twig\Sandbox\SecurityNotAllowedFilterError;
use Twig\Sandbox\SecurityNotAllowedFunctionError;
use Twig\Source;
use Twig\Template;

/* table/page_with_secondary_tabs.twig */
class __TwigTemplate_4a76a81d7c215980b2893b2eece336c90b7057b072288156fc6b9f946f18e2e6 extends \Twig\Template
{
    private $source;
    private $macros = [];

    public function __construct(Environment $env)
    {
        parent::__construct($env);

        $this->source = $this->getSourceContext();

        $this->parent = false;

        $this->blocks = [
            'content' => [$this, 'block_content'],
        ];
    }

    protected function doDisplay(array $context, array $blocks = [])
    {
        $macros = $this->macros;
        // line 1
        if (((($__internal_f607aeef2c31a95a7bf963452dff024ffaeb6aafbe4603f9ca3bec57be8633f4 = ($context["cfg_relation"] ?? null)) && is_array($__internal_f607aeef2c31a95a7bf963452dff024ffaeb6aafbe4603f9ca3bec57be8633f4) || $__internal_f607aeef2c31a95a7bf963452dff024ffaeb6aafbe4603f9ca3bec57be8633f4 instanceof ArrayAccess ? ($__internal_f607aeef2c31a95a7bf963452dff024ffaeb6aafbe4603f9ca3bec57be8633f4["relwork"] ?? null) : null) || ($context["is_foreign_key_supported"] ?? null))) {
            // line 2
            echo "  <ul class=\"nav nav-pills m-2 d-print-none\">
    <li class=\"nav-item\">
      <a href=\"";
            // line 4
            echo PhpMyAdmin\Url::getFromRoute("/table/structure", ["db" => ($context["db"] ?? null), "table" => ($context["table"] ?? null)]);
            echo "\" id=\"table_structure_id\" class=\"nav-link";
            echo (((($context["route"] ?? null) == "/table/structure")) ? (" active") : (""));
            echo "\">
        ";
            // line 5
            echo \PhpMyAdmin\Html\Generator::getIcon("b_props", _gettext("Table structure"), true);
            echo "
      </a>
    </li>

    <li class=\"nav-item\">
      <a href=\"";
            // line 10
            echo PhpMyAdmin\Url::getFromRoute("/table/relation", ["db" => ($context["db"] ?? null), "table" => ($context["table"] ?? null)]);
            echo "\" id=\"table_relation_id\" class=\"nav-link";
            echo (((($context["route"] ?? null) == "/table/relation")) ? (" active") : (""));
            echo "\">
        ";
            // line 11
            echo \PhpMyAdmin\Html\Generator::getIcon("b_relations", _gettext("Relation view"), true);
            echo "
      </a>
    </li>
  </ul>
";
        }
        // line 16
        echo "
<div id=\"structure_content\">
  ";
        // line 18
        $this->displayBlock('content', $context, $blocks);
        // line 19
        echo "</div>
";
    }

    // line 18
    public function block_content($context, array $blocks = [])
    {
        $macros = $this->macros;
    }

    public function getTemplateName()
    {
        return "table/page_with_secondary_tabs.twig";
    }

    public function isTraitable()
    {
        return false;
    }

    public function getDebugInfo()
    {
        return array (  83 => 18,  78 => 19,  76 => 18,  72 => 16,  64 => 11,  58 => 10,  50 => 5,  44 => 4,  40 => 2,  38 => 1,);
    }

    public function getSourceContext()
    {
        return new Source("", "table/page_with_secondary_tabs.twig", "C:\\xampp\\phpMyAdmin\\templates\\table\\page_with_secondary_tabs.twig");
    }
}
