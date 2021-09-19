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

/* sql/profiling_chart.twig */
class __TwigTemplate_3a89fe9e746700aee5abc7cb48c33147c3d89a7f430c34a858abc74e65ee4b99 extends \Twig\Template
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
        echo "<fieldset>
  <legend>";
        // line 2
        echo _gettext("Profiling");
        echo "</legend>
  <div class=\"floatleft\">
    <h3>";
        // line 4
        echo _gettext("Detailed profile");
        echo "</h3>
    <table class=\"pma-table\" id=\"profiletable\">
      <thead>
      <tr>
        <th>
          ";
        // line 9
        echo _gettext("Order");
        // line 10
        echo "          <div class=\"sorticon\"></div>
        </th>
        <th>
          ";
        // line 13
        echo _gettext("State");
        // line 14
        echo "          <div class=\"sorticon\"></div>
        </th>
        <th>
          ";
        // line 17
        echo _gettext("Time");
        // line 18
        echo "          <div class=\"sorticon\"></div>
        </th>
      </tr>
      </thead>
      <tbody>
        ";
        // line 23
        $context['_parent'] = $context;
        $context['_seq'] = twig_ensure_traversable(twig_get_attribute($this->env, $this->source, ($context["profiling"] ?? null), "profile", [], "any", false, false, false, 23));
        $context['loop'] = [
          'parent' => $context['_parent'],
          'index0' => 0,
          'index'  => 1,
          'first'  => true,
        ];
        if (is_array($context['_seq']) || (is_object($context['_seq']) && $context['_seq'] instanceof \Countable)) {
            $length = count($context['_seq']);
            $context['loop']['revindex0'] = $length - 1;
            $context['loop']['revindex'] = $length;
            $context['loop']['length'] = $length;
            $context['loop']['last'] = 1 === $length;
        }
        foreach ($context['_seq'] as $context["_key"] => $context["state"]) {
            // line 24
            echo "          <tr>
            <td>";
            // line 25
            echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["loop"], "index", [], "any", false, false, false, 25), "html", null, true);
            echo "</td>
            <td>";
            // line 26
            echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["state"], "status", [], "any", false, false, false, 26), "html", null, true);
            echo "</td>
            <td class=\"text-right\">
              ";
            // line 28
            echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["state"], "duration", [], "any", false, false, false, 28), "html", null, true);
            echo "s
              <span class=\"rawvalue hide\">";
            // line 29
            echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["state"], "duration_raw", [], "any", false, false, false, 29), "html", null, true);
            echo "</span>
            </td>
          </tr>
        ";
            ++$context['loop']['index0'];
            ++$context['loop']['index'];
            $context['loop']['first'] = false;
            if (isset($context['loop']['length'])) {
                --$context['loop']['revindex0'];
                --$context['loop']['revindex'];
                $context['loop']['last'] = 0 === $context['loop']['revindex0'];
            }
        }
        $_parent = $context['_parent'];
        unset($context['_seq'], $context['_iterated'], $context['_key'], $context['state'], $context['_parent'], $context['loop']);
        $context = array_intersect_key($context, $_parent) + $_parent;
        // line 33
        echo "      </tbody>
    </table>
  </div>

  <div class=\"floatleft\">
    <h3>";
        // line 38
        echo _gettext("Summary by state");
        echo \PhpMyAdmin\Html\MySQLDocumentation::show("general-thread-states");
        echo "</h3>
    <table class=\"pma-table\" id=\"profilesummarytable\">
      <thead>
      <tr>
        <th>
          ";
        // line 43
        echo _gettext("State");
        // line 44
        echo "          <div class=\"sorticon\"></div>
        </th>
        <th>
          ";
        // line 47
        echo _gettext("Total Time");
        // line 48
        echo "          <div class=\"sorticon\"></div>
        </th>
        <th>
          ";
        // line 51
        echo _gettext("% Time");
        // line 52
        echo "          <div class=\"sorticon\"></div>
        </th>
        <th>
          ";
        // line 55
        echo _gettext("Calls");
        // line 56
        echo "          <div class=\"sorticon\"></div>
        </th>
        <th>
          ";
        // line 59
        echo _gettext("ø Time");
        // line 60
        echo "          <div class=\"sorticon\"></div>
        </th>
      </tr>
      </thead>
      <tbody>
        ";
        // line 65
        $context['_parent'] = $context;
        $context['_seq'] = twig_ensure_traversable(twig_get_attribute($this->env, $this->source, ($context["profiling"] ?? null), "states", [], "any", false, false, false, 65));
        foreach ($context['_seq'] as $context["name"] => $context["stats"]) {
            // line 66
            echo "          <tr>
            <td>";
            // line 67
            echo twig_escape_filter($this->env, $context["name"], "html", null, true);
            echo "</td>
            <td class=\"text-right\">
              ";
            // line 69
            echo twig_escape_filter($this->env, PhpMyAdmin\Util::formatNumber(twig_get_attribute($this->env, $this->source, $context["stats"], "total_time", [], "any", false, false, false, 69), 3, 1), "html", null, true);
            echo "s
              <span class=\"rawvalue hide\">";
            // line 70
            echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["stats"], "total_time", [], "any", false, false, false, 70), "html", null, true);
            echo "</span>
            </td>
            <td class=\"text-right\">
              ";
            // line 73
            echo twig_escape_filter($this->env, PhpMyAdmin\Util::formatNumber((100 * (twig_get_attribute($this->env, $this->source, $context["stats"], "total_time", [], "any", false, false, false, 73) / twig_get_attribute($this->env, $this->source, ($context["profiling"] ?? null), "total_time", [], "any", false, false, false, 73))), 0, 2), "html", null, true);
            echo "%
            </td>
            <td class=\"text-right\">";
            // line 75
            echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["stats"], "calls", [], "any", false, false, false, 75), "html", null, true);
            echo "</td>
            <td class=\"text-right\">
              ";
            // line 77
            echo twig_escape_filter($this->env, PhpMyAdmin\Util::formatNumber((twig_get_attribute($this->env, $this->source, $context["stats"], "total_time", [], "any", false, false, false, 77) / twig_get_attribute($this->env, $this->source, $context["stats"], "calls", [], "any", false, false, false, 77)), 3, 1), "html", null, true);
            echo "s
              <span class=\"rawvalue hide\">
                ";
            // line 79
            echo twig_escape_filter($this->env, twig_number_format_filter($this->env, (twig_get_attribute($this->env, $this->source, $context["stats"], "total_time", [], "any", false, false, false, 79) / twig_get_attribute($this->env, $this->source, $context["stats"], "calls", [], "any", false, false, false, 79)), 8, ".", ""), "html", null, true);
            echo "
              </span>
            </td>
          </tr>
        ";
        }
        $_parent = $context['_parent'];
        unset($context['_seq'], $context['_iterated'], $context['name'], $context['stats'], $context['_parent'], $context['loop']);
        $context = array_intersect_key($context, $_parent) + $_parent;
        // line 84
        echo "      </tbody>
    </table>
  </div>
  <div class='clearfloat'></div>

  <div id=\"profilingChartData\" class=\"hide\">";
        // line 90
        echo twig_escape_filter($this->env, json_encode(twig_get_attribute($this->env, $this->source, ($context["profiling"] ?? null), "chart", [], "any", false, false, false, 90)), "html", null, true);
        // line 91
        echo "</div>
  <div id=\"profilingchart\" class=\"hide\"></div>

  <script type=\"text/javascript\">
    AJAX.registerOnload('sql.js', function () {
      Sql.makeProfilingChart();
      Sql.initProfilingTables();
    });
  </script>
</fieldset>
";
    }

    public function getTemplateName()
    {
        return "sql/profiling_chart.twig";
    }

    public function isTraitable()
    {
        return false;
    }

    public function getDebugInfo()
    {
        return array (  237 => 91,  235 => 90,  228 => 84,  217 => 79,  212 => 77,  207 => 75,  202 => 73,  196 => 70,  192 => 69,  187 => 67,  184 => 66,  180 => 65,  173 => 60,  171 => 59,  166 => 56,  164 => 55,  159 => 52,  157 => 51,  152 => 48,  150 => 47,  145 => 44,  143 => 43,  134 => 38,  127 => 33,  109 => 29,  105 => 28,  100 => 26,  96 => 25,  93 => 24,  76 => 23,  69 => 18,  67 => 17,  62 => 14,  60 => 13,  55 => 10,  53 => 9,  45 => 4,  40 => 2,  37 => 1,);
    }

    public function getSourceContext()
    {
        return new Source("", "sql/profiling_chart.twig", "C:\\xampp\\phpMyAdmin\\templates\\sql\\profiling_chart.twig");
    }
}
