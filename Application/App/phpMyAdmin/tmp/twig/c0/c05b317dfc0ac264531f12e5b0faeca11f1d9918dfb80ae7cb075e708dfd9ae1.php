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

/* database/structure/show_create.twig */
class __TwigTemplate_0d844d09e40c84dc7f6c903427763570a8f5361ecf0a9872ff79d9f5424e2b29 extends \Twig\Template
{
    private $source;
    private $macros = [];

    public function __construct(Environment $env)
    {
        parent::__construct($env);

        $this->source = $this->getSourceContext();

        $this->parent = false;

        $this->blocks = [
        ];
    }

    protected function doDisplay(array $context, array $blocks = [])
    {
        $macros = $this->macros;
        // line 1
        echo "<div class=\"show_create_results\">
  <h2>";
        // line 2
        echo _gettext("Showing create queries");
        echo "</h2>

  ";
        // line 4
        if ( !twig_test_empty(twig_get_attribute($this->env, $this->source, ($context["tables"] ?? null), "tables", [], "any", false, false, false, 4))) {
            // line 5
            echo "    <fieldset>
      <legend>";
            // line 6
            echo _gettext("Tables");
            echo "</legend>
      <table class=\"pma-table show_create\">
        <thead>
          <tr>
            <th>";
            // line 10
            echo _gettext("Table");
            echo "</th>
            <th>";
            // line 11
            echo _gettext("Create table");
            echo "</th>
          </tr>
        </thead>
        <tbody>
          ";
            // line 15
            $context['_parent'] = $context;
            $context['_seq'] = twig_ensure_traversable(twig_get_attribute($this->env, $this->source, ($context["tables"] ?? null), "tables", [], "any", false, false, false, 15));
            foreach ($context['_seq'] as $context["_key"] => $context["table"]) {
                // line 16
                echo "            <tr>
              <td><strong>";
                // line 17
                echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["table"], "name", [], "any", false, false, false, 17), "html", null, true);
                echo "</strong></td>
              <td>";
                // line 18
                echo twig_get_attribute($this->env, $this->source, $context["table"], "show_create", [], "any", false, false, false, 18);
                echo "</td>
            </tr>
          ";
            }
            $_parent = $context['_parent'];
            unset($context['_seq'], $context['_iterated'], $context['_key'], $context['table'], $context['_parent'], $context['loop']);
            $context = array_intersect_key($context, $_parent) + $_parent;
            // line 21
            echo "        </tbody>
      </table>
    </fieldset>
  ";
        }
        // line 25
        echo "
  ";
        // line 26
        if ( !twig_test_empty(twig_get_attribute($this->env, $this->source, ($context["tables"] ?? null), "views", [], "any", false, false, false, 26))) {
            // line 27
            echo "    <fieldset>
      <legend>";
            // line 28
            echo _gettext("Views");
            echo "</legend>
      <table class=\"pma-table show_create\">
        <thead>
          <tr>
            <th>";
            // line 32
            echo _gettext("View");
            echo "</th>
            <th>";
            // line 33
            echo _gettext("Create view");
            echo "</th>
          </tr>
        </thead>
        <tbody>
          ";
            // line 37
            $context['_parent'] = $context;
            $context['_seq'] = twig_ensure_traversable(twig_get_attribute($this->env, $this->source, ($context["tables"] ?? null), "views", [], "any", false, false, false, 37));
            foreach ($context['_seq'] as $context["_key"] => $context["view"]) {
                // line 38
                echo "            <tr>
              <td><strong>";
                // line 39
                echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["view"], "name", [], "any", false, false, false, 39), "html", null, true);
                echo "</strong></td>
              <td>";
                // line 40
                echo twig_get_attribute($this->env, $this->source, $context["view"], "show_create", [], "any", false, false, false, 40);
                echo "</td>
            </tr>
          ";
            }
            $_parent = $context['_parent'];
            unset($context['_seq'], $context['_iterated'], $context['_key'], $context['view'], $context['_parent'], $context['loop']);
            $context = array_intersect_key($context, $_parent) + $_parent;
            // line 43
            echo "        </tbody>
      </table>
    </fieldset>
  ";
        }
        // line 47
        echo "</div>
";
    }

    public function getTemplateName()
    {
        return "database/structure/show_create.twig";
    }

    public function isTraitable()
    {
        return false;
    }

    public function getDebugInfo()
    {
        return array (  146 => 47,  140 => 43,  131 => 40,  127 => 39,  124 => 38,  120 => 37,  113 => 33,  109 => 32,  102 => 28,  99 => 27,  97 => 26,  94 => 25,  88 => 21,  79 => 18,  75 => 17,  72 => 16,  68 => 15,  61 => 11,  57 => 10,  50 => 6,  47 => 5,  45 => 4,  40 => 2,  37 => 1,);
    }

    public function getSourceContext()
    {
        return new Source("", "database/structure/show_create.twig", "C:\\xampp\\phpMyAdmin\\templates\\database\\structure\\show_create.twig");
    }
}
