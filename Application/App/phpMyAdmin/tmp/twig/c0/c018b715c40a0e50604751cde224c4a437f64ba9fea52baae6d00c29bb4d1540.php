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

/* sql/bookmark.twig */
class __TwigTemplate_a0f60cbc5493fc24c8eba7ce8cf9c5d8b6ebfca8214fd4ca7dd7b3a2008d9b8f extends \Twig\Template
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
        echo "<form action=\"";
        echo PhpMyAdmin\Url::getFromRoute("/sql");
        echo "\" method=\"post\" class=\"bookmarkQueryForm print_ignore\"
    onsubmit=\"return ! Functions.emptyCheckTheField(this, 'bkm_fields[bkm_label]');\">
    ";
        // line 3
        echo PhpMyAdmin\Url::getHiddenInputs();
        echo "
    <input type=\"hidden\" name=\"db\" value=\"";
        // line 4
        echo twig_escape_filter($this->env, ($context["db"] ?? null), "html", null, true);
        echo "\">
    <input type=\"hidden\" name=\"goto\" value=\"";
        // line 5
        echo twig_escape_filter($this->env, ($context["goto"] ?? null), "html", null, true);
        echo "\">
    <input type=\"hidden\" name=\"bkm_fields[bkm_database]\" value=\"";
        // line 6
        echo twig_escape_filter($this->env, ($context["db"] ?? null), "html", null, true);
        echo "\">
    <input type=\"hidden\" name=\"bkm_fields[bkm_user]\" value=\"";
        // line 7
        echo twig_escape_filter($this->env, ($context["user"] ?? null), "html", null, true);
        echo "\">
    <input type=\"hidden\" name=\"bkm_fields[bkm_sql_query]\" value=\"";
        // line 8
        echo twig_escape_filter($this->env, ($context["sql_query"] ?? null), "html", null, true);
        echo "\">
    <fieldset>
        <legend>
            ";
        // line 11
        echo \PhpMyAdmin\Html\Generator::getIcon("b_bookmark", _gettext("Bookmark this SQL query"), true);
        echo "
        </legend>
        <div class=\"formelement\">
            <label>
                ";
        // line 15
        echo _gettext("Label:");
        // line 16
        echo "                <input type=\"text\" name=\"bkm_fields[bkm_label]\" value=\"\">
            </label>
        </div>
        <div class=\"formelement\">
            <label>
                <input type=\"checkbox\" name=\"bkm_all_users\" value=\"true\">
                ";
        // line 22
        echo _gettext("Let every user access this bookmark");
        // line 23
        echo "            </label>
        </div>
        <div class=\"clearfloat\"></div>
    </fieldset>
    <fieldset class=\"tblFooters\">
        <input type=\"hidden\" name=\"store_bkm\" value=\"1\">
        <input class=\"btn btn-secondary\" type=\"submit\" value=\"";
        // line 29
        echo _gettext("Bookmark this SQL query");
        echo "\">
    </fieldset>
</form>
";
    }

    public function getTemplateName()
    {
        return "sql/bookmark.twig";
    }

    public function isTraitable()
    {
        return false;
    }

    public function getDebugInfo()
    {
        return array (  96 => 29,  88 => 23,  86 => 22,  78 => 16,  76 => 15,  69 => 11,  63 => 8,  59 => 7,  55 => 6,  51 => 5,  47 => 4,  43 => 3,  37 => 1,);
    }

    public function getSourceContext()
    {
        return new Source("", "sql/bookmark.twig", "C:\\xampp\\phpMyAdmin\\templates\\sql\\bookmark.twig");
    }
}
