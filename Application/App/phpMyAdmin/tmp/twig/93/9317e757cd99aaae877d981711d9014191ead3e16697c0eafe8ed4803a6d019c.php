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

/* table/structure/display_structure.twig */
class __TwigTemplate_e76d3c622f0f64c3d9452b02207af7dbc2e1321fe6ca476e73b106b4eae2ffbe extends \Twig\Template
{
    private $source;
    private $macros = [];

    public function __construct(Environment $env)
    {
        parent::__construct($env);

        $this->source = $this->getSourceContext();

        $this->blocks = [
            'content' => [$this, 'block_content'],
        ];
    }

    protected function doGetParent(array $context)
    {
        // line 1
        return "table/page_with_secondary_tabs.twig";
    }

    protected function doDisplay(array $context, array $blocks = [])
    {
        $macros = $this->macros;
        $this->parent = $this->loadTemplate("table/page_with_secondary_tabs.twig", "table/structure/display_structure.twig", 1);
        $this->parent->display($context, array_merge($this->blocks, $blocks));
    }

    // line 2
    public function block_content($context, array $blocks = [])
    {
        $macros = $this->macros;
        // line 3
        echo "<h1 class=\"d-none d-print-block\">";
        echo twig_escape_filter($this->env, ($context["table"] ?? null), "html", null, true);
        echo "</h1>
<form method=\"post\" action=\"";
        // line 4
        echo PhpMyAdmin\Url::getFromRoute("/table/structure");
        echo "\" name=\"fieldsForm\" id=\"fieldsForm\"
    class=\"ajax";
        // line 5
        echo ((($context["hide_structure_actions"] ?? null)) ? (" HideStructureActions") : (""));
        echo "\">
    ";
        // line 6
        echo PhpMyAdmin\Url::getHiddenInputs(($context["db"] ?? null), ($context["table"] ?? null));
        echo "
    <input type=\"hidden\" name=\"table_type\" value=";
        // line 8
        if (($context["db_is_system_schema"] ?? null)) {
            // line 9
            echo "\"information_schema\"";
        } elseif (        // line 10
($context["tbl_is_view"] ?? null)) {
            // line 11
            echo "\"view\"";
        } else {
            // line 13
            echo "\"table\"";
        }
        // line 14
        echo ">
    <div class=\"table-responsive-md\">
    <table id=\"tablestructure\" class=\"table table-light table-striped table-hover w-auto\">
        ";
        // line 18
        echo "        <thead class=\"thead-light\">
            <tr>
                <th class=\"print_ignore\"></th>
                <th>#</th>
                <th>";
        // line 22
        echo _gettext("Name");
        echo "</th>
                <th>";
        // line 23
        echo _gettext("Type");
        echo "</th>
                <th>";
        // line 24
        echo _gettext("Collation");
        echo "</th>
                <th>";
        // line 25
        echo _gettext("Attributes");
        echo "</th>
                <th>";
        // line 26
        echo _gettext("Null");
        echo "</th>
                <th>";
        // line 27
        echo _gettext("Default");
        echo "</th>
                ";
        // line 28
        if (($context["show_column_comments"] ?? null)) {
            // line 29
            echo "<th>";
            echo _gettext("Comments");
            echo "</th>";
        }
        // line 31
        echo "                <th>";
        echo _gettext("Extra");
        echo "</th>
                ";
        // line 33
        echo "                ";
        if (( !($context["db_is_system_schema"] ?? null) &&  !($context["tbl_is_view"] ?? null))) {
            // line 34
            echo "                    <th colspan=\"";
            echo ((PhpMyAdmin\Util::showIcons("ActionLinksMode")) ? ("8") : ("9"));
            // line 35
            echo "\" class=\"action print_ignore\">";
            echo _gettext("Action");
            echo "</th>
                ";
        }
        // line 37
        echo "            </tr>
        </thead>
        <tbody>
        ";
        // line 41
        echo "        ";
        $context["rownum"] = 0;
        // line 42
        echo "        ";
        $context['_parent'] = $context;
        $context['_seq'] = twig_ensure_traversable(($context["fields"] ?? null));
        foreach ($context['_seq'] as $context["_key"] => $context["row"]) {
            // line 43
            echo "            ";
            $context["rownum"] = (($context["rownum"] ?? null) + 1);
            // line 44
            echo "
            ";
            // line 45
            $context["extracted_columnspec"] = (($__internal_f607aeef2c31a95a7bf963452dff024ffaeb6aafbe4603f9ca3bec57be8633f4 = ($context["extracted_columnspecs"] ?? null)) && is_array($__internal_f607aeef2c31a95a7bf963452dff024ffaeb6aafbe4603f9ca3bec57be8633f4) || $__internal_f607aeef2c31a95a7bf963452dff024ffaeb6aafbe4603f9ca3bec57be8633f4 instanceof ArrayAccess ? ($__internal_f607aeef2c31a95a7bf963452dff024ffaeb6aafbe4603f9ca3bec57be8633f4[($context["rownum"] ?? null)] ?? null) : null);
            // line 46
            echo "            ";
            $context["field_name"] = twig_escape_filter($this->env, (($__internal_62824350bc4502ee19dbc2e99fc6bdd3bd90e7d8dd6e72f42c35efd048542144 = $context["row"]) && is_array($__internal_62824350bc4502ee19dbc2e99fc6bdd3bd90e7d8dd6e72f42c35efd048542144) || $__internal_62824350bc4502ee19dbc2e99fc6bdd3bd90e7d8dd6e72f42c35efd048542144 instanceof ArrayAccess ? ($__internal_62824350bc4502ee19dbc2e99fc6bdd3bd90e7d8dd6e72f42c35efd048542144["Field"] ?? null) : null));
            // line 47
            echo "            ";
            // line 48
            echo "            ";
            $context["comments"] = (($__internal_1cfccaec8dd2e8578ccb026fbe7f2e7e29ac2ed5deb976639c5fc99a6ea8583b = ($context["row_comments"] ?? null)) && is_array($__internal_1cfccaec8dd2e8578ccb026fbe7f2e7e29ac2ed5deb976639c5fc99a6ea8583b) || $__internal_1cfccaec8dd2e8578ccb026fbe7f2e7e29ac2ed5deb976639c5fc99a6ea8583b instanceof ArrayAccess ? ($__internal_1cfccaec8dd2e8578ccb026fbe7f2e7e29ac2ed5deb976639c5fc99a6ea8583b[($context["rownum"] ?? null)] ?? null) : null);
            // line 49
            echo "            ";
            // line 50
            echo "
        <tr>
            <td class=\"text-center print_ignore\">
                <input type=\"checkbox\" class=\"checkall\" name=\"selected_fld[]\" value=\"";
            // line 53
            echo twig_escape_filter($this->env, (($__internal_68aa442c1d43d3410ea8f958ba9090f3eaa9a76f8de8fc9be4d6c7389ba28002 = $context["row"]) && is_array($__internal_68aa442c1d43d3410ea8f958ba9090f3eaa9a76f8de8fc9be4d6c7389ba28002) || $__internal_68aa442c1d43d3410ea8f958ba9090f3eaa9a76f8de8fc9be4d6c7389ba28002 instanceof ArrayAccess ? ($__internal_68aa442c1d43d3410ea8f958ba9090f3eaa9a76f8de8fc9be4d6c7389ba28002["Field"] ?? null) : null), "html", null, true);
            echo "\" id=\"checkbox_row_";
            echo twig_escape_filter($this->env, ($context["rownum"] ?? null), "html", null, true);
            echo "\">
            </td>
            <td class=\"right\">";
            // line 55
            echo twig_escape_filter($this->env, ($context["rownum"] ?? null), "html", null, true);
            echo "</td>
            <th class=\"nowrap\">
                <label for=\"checkbox_row_";
            // line 57
            echo twig_escape_filter($this->env, ($context["rownum"] ?? null), "html", null, true);
            echo "\">
                    ";
            // line 58
            if (twig_get_attribute($this->env, $this->source, twig_get_attribute($this->env, $this->source, ($context["displayed_fields"] ?? null), ($context["rownum"] ?? null), [], "array", false, true, false, 58), "comment", [], "any", true, true, false, 58)) {
                // line 59
                echo "                        <span class=\"commented_column\" title=\"";
                echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, (($__internal_d7fc55f1a54b629533d60b43063289db62e68921ee7a5f8de562bd9d4a2b7ad4 = ($context["displayed_fields"] ?? null)) && is_array($__internal_d7fc55f1a54b629533d60b43063289db62e68921ee7a5f8de562bd9d4a2b7ad4) || $__internal_d7fc55f1a54b629533d60b43063289db62e68921ee7a5f8de562bd9d4a2b7ad4 instanceof ArrayAccess ? ($__internal_d7fc55f1a54b629533d60b43063289db62e68921ee7a5f8de562bd9d4a2b7ad4[($context["rownum"] ?? null)] ?? null) : null), "comment", [], "any", false, false, false, 59), "html", null, true);
                echo "\">";
                echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, (($__internal_01476f8db28655ee4ee02ea2d17dd5a92599be76304f08cd8bc0e05aced30666 = ($context["displayed_fields"] ?? null)) && is_array($__internal_01476f8db28655ee4ee02ea2d17dd5a92599be76304f08cd8bc0e05aced30666) || $__internal_01476f8db28655ee4ee02ea2d17dd5a92599be76304f08cd8bc0e05aced30666 instanceof ArrayAccess ? ($__internal_01476f8db28655ee4ee02ea2d17dd5a92599be76304f08cd8bc0e05aced30666[($context["rownum"] ?? null)] ?? null) : null), "text", [], "any", false, false, false, 59), "html", null, true);
                echo "</span>
                    ";
            } else {
                // line 61
                echo "                        ";
                echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, (($__internal_01c35b74bd85735098add188b3f8372ba465b232ab8298cb582c60f493d3c22e = ($context["displayed_fields"] ?? null)) && is_array($__internal_01c35b74bd85735098add188b3f8372ba465b232ab8298cb582c60f493d3c22e) || $__internal_01c35b74bd85735098add188b3f8372ba465b232ab8298cb582c60f493d3c22e instanceof ArrayAccess ? ($__internal_01c35b74bd85735098add188b3f8372ba465b232ab8298cb582c60f493d3c22e[($context["rownum"] ?? null)] ?? null) : null), "text", [], "any", false, false, false, 61), "html", null, true);
                echo "
                    ";
            }
            // line 63
            echo "                    ";
            echo twig_get_attribute($this->env, $this->source, (($__internal_63ad1f9a2bf4db4af64b010785e9665558fdcac0e8db8b5b413ed986c62dbb52 = ($context["displayed_fields"] ?? null)) && is_array($__internal_63ad1f9a2bf4db4af64b010785e9665558fdcac0e8db8b5b413ed986c62dbb52) || $__internal_63ad1f9a2bf4db4af64b010785e9665558fdcac0e8db8b5b413ed986c62dbb52 instanceof ArrayAccess ? ($__internal_63ad1f9a2bf4db4af64b010785e9665558fdcac0e8db8b5b413ed986c62dbb52[($context["rownum"] ?? null)] ?? null) : null), "icon", [], "any", false, false, false, 63);
            echo "
                </label>
            </th>
            <td";
            // line 66
            echo (((("set" != (($__internal_f10a4cc339617934220127f034125576ed229e948660ebac906a15846d52f136 = ($context["extracted_columnspec"] ?? null)) && is_array($__internal_f10a4cc339617934220127f034125576ed229e948660ebac906a15846d52f136) || $__internal_f10a4cc339617934220127f034125576ed229e948660ebac906a15846d52f136 instanceof ArrayAccess ? ($__internal_f10a4cc339617934220127f034125576ed229e948660ebac906a15846d52f136["type"] ?? null) : null)) && ("enum" != (($__internal_887a873a4dc3cf8bd4f99c487b4c7727999c350cc3a772414714e49a195e4386 = ($context["extracted_columnspec"] ?? null)) && is_array($__internal_887a873a4dc3cf8bd4f99c487b4c7727999c350cc3a772414714e49a195e4386) || $__internal_887a873a4dc3cf8bd4f99c487b4c7727999c350cc3a772414714e49a195e4386 instanceof ArrayAccess ? ($__internal_887a873a4dc3cf8bd4f99c487b4c7727999c350cc3a772414714e49a195e4386["type"] ?? null) : null)))) ? (" class=\"nowrap\"") : (""));
            echo ">
                <bdo dir=\"ltr\" lang=\"en\">
                    ";
            // line 68
            echo (($__internal_d527c24a729d38501d770b40a0d25e1ce8a7f0bff897cc4f8f449ba71fcff3d9 = ($context["extracted_columnspec"] ?? null)) && is_array($__internal_d527c24a729d38501d770b40a0d25e1ce8a7f0bff897cc4f8f449ba71fcff3d9) || $__internal_d527c24a729d38501d770b40a0d25e1ce8a7f0bff897cc4f8f449ba71fcff3d9 instanceof ArrayAccess ? ($__internal_d527c24a729d38501d770b40a0d25e1ce8a7f0bff897cc4f8f449ba71fcff3d9["displayed_type"] ?? null) : null);
            echo "
                    ";
            // line 69
            if ((((($context["relation_commwork"] ?? null) && ($context["relation_mimework"] ?? null)) && ($context["browse_mime"] ?? null)) && twig_get_attribute($this->env, $this->source, twig_get_attribute($this->env, $this->source,             // line 70
($context["mime_map"] ?? null), (($__internal_f6dde3a1020453fdf35e718e94f93ce8eb8803b28cc77a665308e14bbe8572ae = $context["row"]) && is_array($__internal_f6dde3a1020453fdf35e718e94f93ce8eb8803b28cc77a665308e14bbe8572ae) || $__internal_f6dde3a1020453fdf35e718e94f93ce8eb8803b28cc77a665308e14bbe8572ae instanceof ArrayAccess ? ($__internal_f6dde3a1020453fdf35e718e94f93ce8eb8803b28cc77a665308e14bbe8572ae["Field"] ?? null) : null), [], "array", false, true, false, 70), "mimetype", [], "array", true, true, false, 70))) {
                // line 71
                echo "                        <br>";
                echo _gettext("Media type:");
                echo " ";
                echo twig_escape_filter($this->env, twig_lower_filter($this->env, twig_replace_filter((($__internal_25c0fab8152b8dd6b90603159c0f2e8a936a09ab76edb5e4d7bc95d9a8d2dc8f = (($__internal_f769f712f3484f00110c86425acea59f5af2752239e2e8596bcb6effeb425b40 = ($context["mime_map"] ?? null)) && is_array($__internal_f769f712f3484f00110c86425acea59f5af2752239e2e8596bcb6effeb425b40) || $__internal_f769f712f3484f00110c86425acea59f5af2752239e2e8596bcb6effeb425b40 instanceof ArrayAccess ? ($__internal_f769f712f3484f00110c86425acea59f5af2752239e2e8596bcb6effeb425b40[(($__internal_98e944456c0f58b2585e4aa36e3a7e43f4b7c9038088f0f056004af41f4a007f = $context["row"]) && is_array($__internal_98e944456c0f58b2585e4aa36e3a7e43f4b7c9038088f0f056004af41f4a007f) || $__internal_98e944456c0f58b2585e4aa36e3a7e43f4b7c9038088f0f056004af41f4a007f instanceof ArrayAccess ? ($__internal_98e944456c0f58b2585e4aa36e3a7e43f4b7c9038088f0f056004af41f4a007f["Field"] ?? null) : null)] ?? null) : null)) && is_array($__internal_25c0fab8152b8dd6b90603159c0f2e8a936a09ab76edb5e4d7bc95d9a8d2dc8f) || $__internal_25c0fab8152b8dd6b90603159c0f2e8a936a09ab76edb5e4d7bc95d9a8d2dc8f instanceof ArrayAccess ? ($__internal_25c0fab8152b8dd6b90603159c0f2e8a936a09ab76edb5e4d7bc95d9a8d2dc8f["mimetype"] ?? null) : null), ["_" => "/"])), "html", null, true);
                echo "
                    ";
            }
            // line 73
            echo "                </bdo>
            </td>
            <td>
            ";
            // line 76
            if ( !twig_test_empty((($__internal_a06a70691a7ca361709a372174fa669f5ee1c1e4ed302b3a5b61c10c80c02760 = $context["row"]) && is_array($__internal_a06a70691a7ca361709a372174fa669f5ee1c1e4ed302b3a5b61c10c80c02760) || $__internal_a06a70691a7ca361709a372174fa669f5ee1c1e4ed302b3a5b61c10c80c02760 instanceof ArrayAccess ? ($__internal_a06a70691a7ca361709a372174fa669f5ee1c1e4ed302b3a5b61c10c80c02760["Collation"] ?? null) : null))) {
                // line 77
                echo "                <dfn title=\"";
                echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, (($__internal_653499042eb14fd8415489ba6fa87c1e85cff03392e9f57b26d0da09b9be82ce = ($context["collations"] ?? null)) && is_array($__internal_653499042eb14fd8415489ba6fa87c1e85cff03392e9f57b26d0da09b9be82ce) || $__internal_653499042eb14fd8415489ba6fa87c1e85cff03392e9f57b26d0da09b9be82ce instanceof ArrayAccess ? ($__internal_653499042eb14fd8415489ba6fa87c1e85cff03392e9f57b26d0da09b9be82ce[(($__internal_ba9f0a3bb95c082f61c9fbf892a05514d732703d52edc77b51f2e6284135900b = $context["row"]) && is_array($__internal_ba9f0a3bb95c082f61c9fbf892a05514d732703d52edc77b51f2e6284135900b) || $__internal_ba9f0a3bb95c082f61c9fbf892a05514d732703d52edc77b51f2e6284135900b instanceof ArrayAccess ? ($__internal_ba9f0a3bb95c082f61c9fbf892a05514d732703d52edc77b51f2e6284135900b["Collation"] ?? null) : null)] ?? null) : null), "description", [], "any", false, false, false, 77), "html", null, true);
                echo "\">";
                echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, (($__internal_73db8eef4d2582468dab79a6b09c77ce3b48675a610afd65a1f325b68804a60c = ($context["collations"] ?? null)) && is_array($__internal_73db8eef4d2582468dab79a6b09c77ce3b48675a610afd65a1f325b68804a60c) || $__internal_73db8eef4d2582468dab79a6b09c77ce3b48675a610afd65a1f325b68804a60c instanceof ArrayAccess ? ($__internal_73db8eef4d2582468dab79a6b09c77ce3b48675a610afd65a1f325b68804a60c[(($__internal_d8ad5934f1874c52fa2ac9a4dfae52038b39b8b03cfc82eeb53de6151d883972 = $context["row"]) && is_array($__internal_d8ad5934f1874c52fa2ac9a4dfae52038b39b8b03cfc82eeb53de6151d883972) || $__internal_d8ad5934f1874c52fa2ac9a4dfae52038b39b8b03cfc82eeb53de6151d883972 instanceof ArrayAccess ? ($__internal_d8ad5934f1874c52fa2ac9a4dfae52038b39b8b03cfc82eeb53de6151d883972["Collation"] ?? null) : null)] ?? null) : null), "name", [], "any", false, false, false, 77), "html", null, true);
                echo "</dfn>
            ";
            }
            // line 79
            echo "            </td>
            <td class=\"column_attribute nowrap\">";
            // line 80
            echo twig_escape_filter($this->env, (($__internal_df39c71428eaf37baa1ea2198679e0077f3699bdd31bb5ba10d084710b9da216 = ($context["attributes"] ?? null)) && is_array($__internal_df39c71428eaf37baa1ea2198679e0077f3699bdd31bb5ba10d084710b9da216) || $__internal_df39c71428eaf37baa1ea2198679e0077f3699bdd31bb5ba10d084710b9da216 instanceof ArrayAccess ? ($__internal_df39c71428eaf37baa1ea2198679e0077f3699bdd31bb5ba10d084710b9da216[($context["rownum"] ?? null)] ?? null) : null), "html", null, true);
            echo "</td>
            <td>";
            // line 81
            echo twig_escape_filter($this->env, ((((($__internal_bf0e189d688dc2ad611b50a437a32d3692fb6b8be90d2228617cfa6db44e75c0 = $context["row"]) && is_array($__internal_bf0e189d688dc2ad611b50a437a32d3692fb6b8be90d2228617cfa6db44e75c0) || $__internal_bf0e189d688dc2ad611b50a437a32d3692fb6b8be90d2228617cfa6db44e75c0 instanceof ArrayAccess ? ($__internal_bf0e189d688dc2ad611b50a437a32d3692fb6b8be90d2228617cfa6db44e75c0["Null"] ?? null) : null) == "YES")) ? (_gettext("Yes")) : (_gettext("No"))), "html", null, true);
            echo "</td>
            <td class=\"nowrap\">
                ";
            // line 83
            if ( !(null === (($__internal_674c0abf302105af78b0a38907d86c5dd0028bdc3ee5f24bf52771a16487760c = $context["row"]) && is_array($__internal_674c0abf302105af78b0a38907d86c5dd0028bdc3ee5f24bf52771a16487760c) || $__internal_674c0abf302105af78b0a38907d86c5dd0028bdc3ee5f24bf52771a16487760c instanceof ArrayAccess ? ($__internal_674c0abf302105af78b0a38907d86c5dd0028bdc3ee5f24bf52771a16487760c["Default"] ?? null) : null))) {
                // line 84
                echo "                    ";
                if (((($__internal_dd839fbfcab68823c49af471c7df7659a500fe72e71b58d6b80d896bdb55e75f = ($context["extracted_columnspec"] ?? null)) && is_array($__internal_dd839fbfcab68823c49af471c7df7659a500fe72e71b58d6b80d896bdb55e75f) || $__internal_dd839fbfcab68823c49af471c7df7659a500fe72e71b58d6b80d896bdb55e75f instanceof ArrayAccess ? ($__internal_dd839fbfcab68823c49af471c7df7659a500fe72e71b58d6b80d896bdb55e75f["type"] ?? null) : null) == "bit")) {
                    // line 85
                    echo "                        ";
                    echo twig_escape_filter($this->env, PhpMyAdmin\Util::convertBitDefaultValue((($__internal_a7ed47878554bdc32b70e1ba5ccc67d2302196876fbf62b4c853b20cb9e029fc = $context["row"]) && is_array($__internal_a7ed47878554bdc32b70e1ba5ccc67d2302196876fbf62b4c853b20cb9e029fc) || $__internal_a7ed47878554bdc32b70e1ba5ccc67d2302196876fbf62b4c853b20cb9e029fc instanceof ArrayAccess ? ($__internal_a7ed47878554bdc32b70e1ba5ccc67d2302196876fbf62b4c853b20cb9e029fc["Default"] ?? null) : null)), "html", null, true);
                    echo "
                    ";
                } else {
                    // line 87
                    echo "                        ";
                    echo twig_escape_filter($this->env, (($__internal_e5d7b41e16b744b68da1e9bb49047b8028ced86c782900009b4b4029b83d4b55 = $context["row"]) && is_array($__internal_e5d7b41e16b744b68da1e9bb49047b8028ced86c782900009b4b4029b83d4b55) || $__internal_e5d7b41e16b744b68da1e9bb49047b8028ced86c782900009b4b4029b83d4b55 instanceof ArrayAccess ? ($__internal_e5d7b41e16b744b68da1e9bb49047b8028ced86c782900009b4b4029b83d4b55["Default"] ?? null) : null), "html", null, true);
                    echo "
                    ";
                }
                // line 89
                echo "                ";
            } elseif (((($__internal_9e93f398968fa0576dce82fd00f280e95c734ad3f84e7816ff09158ae224f5ba = $context["row"]) && is_array($__internal_9e93f398968fa0576dce82fd00f280e95c734ad3f84e7816ff09158ae224f5ba) || $__internal_9e93f398968fa0576dce82fd00f280e95c734ad3f84e7816ff09158ae224f5ba instanceof ArrayAccess ? ($__internal_9e93f398968fa0576dce82fd00f280e95c734ad3f84e7816ff09158ae224f5ba["Null"] ?? null) : null) == "YES")) {
                // line 90
                echo "                    <em>NULL</em>
                ";
            } else {
                // line 92
                echo "                    <em>";
                echo _pgettext(                "None for default", "None");
                echo "</em>
                ";
            }
            // line 94
            echo "            </td>
            ";
            // line 95
            if (($context["show_column_comments"] ?? null)) {
                // line 96
                echo "                <td>
                    ";
                // line 97
                echo twig_escape_filter($this->env, ($context["comments"] ?? null), "html", null, true);
                echo "
                </td>
            ";
            }
            // line 100
            echo "            <td class=\"nowrap\">";
            echo twig_escape_filter($this->env, twig_upper_filter($this->env, (($__internal_0795e3de58b6454b051261c0c2b5be48852e17f25b59d4aeef29fb07c614bd78 = $context["row"]) && is_array($__internal_0795e3de58b6454b051261c0c2b5be48852e17f25b59d4aeef29fb07c614bd78) || $__internal_0795e3de58b6454b051261c0c2b5be48852e17f25b59d4aeef29fb07c614bd78 instanceof ArrayAccess ? ($__internal_0795e3de58b6454b051261c0c2b5be48852e17f25b59d4aeef29fb07c614bd78["Extra"] ?? null) : null)), "html", null, true);
            echo "</td>
            ";
            // line 101
            if (( !($context["tbl_is_view"] ?? null) &&  !($context["db_is_system_schema"] ?? null))) {
                // line 102
                echo "                <td class=\"edit text-center print_ignore\">
                    <a class=\"change_column_anchor ajax\" href=\"";
                // line 103
                echo PhpMyAdmin\Url::getFromRoute("/table/structure/change", ["db" =>                 // line 104
($context["db"] ?? null), "table" =>                 // line 105
($context["table"] ?? null), "field" => (($__internal_fecb0565c93d0b979a95c352ff76e401e0ae0c73bb8d3b443c8c6133e1c190de =                 // line 106
$context["row"]) && is_array($__internal_fecb0565c93d0b979a95c352ff76e401e0ae0c73bb8d3b443c8c6133e1c190de) || $__internal_fecb0565c93d0b979a95c352ff76e401e0ae0c73bb8d3b443c8c6133e1c190de instanceof ArrayAccess ? ($__internal_fecb0565c93d0b979a95c352ff76e401e0ae0c73bb8d3b443c8c6133e1c190de["Field"] ?? null) : null), "change_column" => 1]);
                // line 108
                echo "\">
                      ";
                // line 109
                echo \PhpMyAdmin\Html\Generator::getIcon("b_edit", _gettext("Change"));
                echo "
                    </a>
                </td>
                <td class=\"drop text-center print_ignore\">
                    <a class=\"drop_column_anchor ajax\" href=\"";
                // line 113
                echo PhpMyAdmin\Url::getFromRoute("/sql");
                echo "\" data-post=\"";
                echo PhpMyAdmin\Url::getCommon(["db" =>                 // line 114
($context["db"] ?? null), "table" =>                 // line 115
($context["table"] ?? null), "sql_query" => (((("ALTER TABLE " . PhpMyAdmin\Util::backquote(                // line 116
($context["table"] ?? null))) . " DROP ") . PhpMyAdmin\Util::backquote((($__internal_87570a635eac7f6e150744bd218085d17aff15d92d9c80a66d3b911e3355b828 = $context["row"]) && is_array($__internal_87570a635eac7f6e150744bd218085d17aff15d92d9c80a66d3b911e3355b828) || $__internal_87570a635eac7f6e150744bd218085d17aff15d92d9c80a66d3b911e3355b828 instanceof ArrayAccess ? ($__internal_87570a635eac7f6e150744bd218085d17aff15d92d9c80a66d3b911e3355b828["Field"] ?? null) : null))) . ";"), "dropped_column" => (($__internal_17b5b5f9aaeec4b528bfeed02b71f624021d6a52d927f441de2f2204d0e527cd =                 // line 117
$context["row"]) && is_array($__internal_17b5b5f9aaeec4b528bfeed02b71f624021d6a52d927f441de2f2204d0e527cd) || $__internal_17b5b5f9aaeec4b528bfeed02b71f624021d6a52d927f441de2f2204d0e527cd instanceof ArrayAccess ? ($__internal_17b5b5f9aaeec4b528bfeed02b71f624021d6a52d927f441de2f2204d0e527cd["Field"] ?? null) : null), "purge" => true, "message_to_show" => sprintf(_gettext("Column %s has been dropped."), twig_escape_filter($this->env, (($__internal_0db9a23306660395861a0528381e0668025e56a8a99f399e9ec23a4b392422d6 =                 // line 119
$context["row"]) && is_array($__internal_0db9a23306660395861a0528381e0668025e56a8a99f399e9ec23a4b392422d6) || $__internal_0db9a23306660395861a0528381e0668025e56a8a99f399e9ec23a4b392422d6 instanceof ArrayAccess ? ($__internal_0db9a23306660395861a0528381e0668025e56a8a99f399e9ec23a4b392422d6["Field"] ?? null) : null)))]);
                // line 120
                echo "\">
                      ";
                // line 121
                echo \PhpMyAdmin\Html\Generator::getIcon("b_drop", _gettext("Drop"));
                echo "
                    </a>
                </td>
            ";
            }
            // line 125
            echo "
            ";
            // line 126
            if (( !($context["tbl_is_view"] ?? null) &&  !($context["db_is_system_schema"] ?? null))) {
                // line 127
                echo "                ";
                $context["type"] = (( !twig_test_empty((($__internal_0a23ad2f11a348e49c87410947e20d5a4e711234ce49927662da5dddac687855 = ($context["extracted_columnspec"] ?? null)) && is_array($__internal_0a23ad2f11a348e49c87410947e20d5a4e711234ce49927662da5dddac687855) || $__internal_0a23ad2f11a348e49c87410947e20d5a4e711234ce49927662da5dddac687855 instanceof ArrayAccess ? ($__internal_0a23ad2f11a348e49c87410947e20d5a4e711234ce49927662da5dddac687855["print_type"] ?? null) : null))) ? ((($__internal_0228c5445a74540c89ea8a758478d405796357800f8af831a7f7e1e2c0159d9b = ($context["extracted_columnspec"] ?? null)) && is_array($__internal_0228c5445a74540c89ea8a758478d405796357800f8af831a7f7e1e2c0159d9b) || $__internal_0228c5445a74540c89ea8a758478d405796357800f8af831a7f7e1e2c0159d9b instanceof ArrayAccess ? ($__internal_0228c5445a74540c89ea8a758478d405796357800f8af831a7f7e1e2c0159d9b["print_type"] ?? null) : null)) : (""));
                // line 128
                echo "                <td class=\"print_ignore\">
                    <ul class=\"table-structure-actions resizable-menu\">
                        ";
                // line 130
                if (($context["hide_structure_actions"] ?? null)) {
                    // line 131
                    echo "                            <li class=\"submenu shown\">
                                <a href=\"#\" class=\"tab nowrap\">";
                    // line 132
                    echo \PhpMyAdmin\Html\Generator::getIcon("b_more", _gettext("More"));
                    echo "</a>
                                <ul>
                        ";
                }
                // line 135
                echo "
                        <li class=\"primary nowrap\">
                          ";
                // line 137
                if (((((($context["type"] ?? null) == "text") || (($context["type"] ?? null) == "blob")) || (($context["tbl_storage_engine"] ?? null) == "ARCHIVE")) || (($context["primary"] ?? null) && twig_get_attribute($this->env, $this->source, ($context["primary"] ?? null), "hasColumn", [0 => ($context["field_name"] ?? null)], "method", false, false, false, 137)))) {
                    // line 138
                    echo "                            ";
                    echo \PhpMyAdmin\Html\Generator::getIcon("bd_primary", _gettext("Primary"));
                    echo "
                          ";
                } else {
                    // line 140
                    echo "                            <a rel=\"samepage\" class=\"ajax add_key print_ignore add_primary_key_anchor\" href=\"";
                    echo PhpMyAdmin\Url::getFromRoute("/table/structure/add-key");
                    echo "\" data-post=\"";
                    echo PhpMyAdmin\Url::getCommon(["db" =>                     // line 141
($context["db"] ?? null), "table" =>                     // line 142
($context["table"] ?? null), "sql_query" => ((((("ALTER TABLE " . PhpMyAdmin\Util::backquote(                    // line 143
($context["table"] ?? null))) . ((($context["primary"] ?? null)) ? (" DROP PRIMARY KEY,") : (""))) . " ADD PRIMARY KEY(") . PhpMyAdmin\Util::backquote((($__internal_6fb04c4457ec9ffa7dd6fd2300542be8b961b6e5f7858a80a282f47b43ddae5f = $context["row"]) && is_array($__internal_6fb04c4457ec9ffa7dd6fd2300542be8b961b6e5f7858a80a282f47b43ddae5f) || $__internal_6fb04c4457ec9ffa7dd6fd2300542be8b961b6e5f7858a80a282f47b43ddae5f instanceof ArrayAccess ? ($__internal_6fb04c4457ec9ffa7dd6fd2300542be8b961b6e5f7858a80a282f47b43ddae5f["Field"] ?? null) : null))) . ");"), "message_to_show" => sprintf(_gettext("A primary key has been added on %s."), twig_escape_filter($this->env, (($__internal_417a1a95b289c75779f33186a6dc0b71d01f257b68beae7dcb9d2d769acca0e0 =                     // line 144
$context["row"]) && is_array($__internal_417a1a95b289c75779f33186a6dc0b71d01f257b68beae7dcb9d2d769acca0e0) || $__internal_417a1a95b289c75779f33186a6dc0b71d01f257b68beae7dcb9d2d769acca0e0 instanceof ArrayAccess ? ($__internal_417a1a95b289c75779f33186a6dc0b71d01f257b68beae7dcb9d2d769acca0e0["Field"] ?? null) : null)))]);
                    // line 145
                    echo "\">
                              ";
                    // line 146
                    echo \PhpMyAdmin\Html\Generator::getIcon("b_primary", _gettext("Primary"));
                    echo "
                            </a>
                          ";
                }
                // line 149
                echo "                        </li>

                        <li class=\"add_unique unique nowrap\">
                          ";
                // line 152
                if (((((($context["type"] ?? null) == "text") || (($context["type"] ?? null) == "blob")) || (($context["tbl_storage_engine"] ?? null) == "ARCHIVE")) || twig_in_filter(($context["field_name"] ?? null), ($context["columns_with_unique_index"] ?? null)))) {
                    // line 153
                    echo "                            ";
                    echo \PhpMyAdmin\Html\Generator::getIcon("bd_unique", _gettext("Unique"));
                    echo "
                          ";
                } else {
                    // line 155
                    echo "                            <a rel=\"samepage\" class=\"ajax add_key print_ignore add_unique_anchor\" href=\"";
                    echo PhpMyAdmin\Url::getFromRoute("/table/structure/add-key");
                    echo "\" data-post=\"";
                    echo PhpMyAdmin\Url::getCommon(["db" =>                     // line 156
($context["db"] ?? null), "table" =>                     // line 157
($context["table"] ?? null), "sql_query" => (((("ALTER TABLE " . PhpMyAdmin\Util::backquote(                    // line 158
($context["table"] ?? null))) . " ADD UNIQUE(") . PhpMyAdmin\Util::backquote((($__internal_af3439635eb343262861f05093b3dcce5d4dae1e20a47bc25a2eef28135b0d55 = $context["row"]) && is_array($__internal_af3439635eb343262861f05093b3dcce5d4dae1e20a47bc25a2eef28135b0d55) || $__internal_af3439635eb343262861f05093b3dcce5d4dae1e20a47bc25a2eef28135b0d55 instanceof ArrayAccess ? ($__internal_af3439635eb343262861f05093b3dcce5d4dae1e20a47bc25a2eef28135b0d55["Field"] ?? null) : null))) . ");"), "message_to_show" => sprintf(_gettext("An index has been added on %s."), twig_escape_filter($this->env, (($__internal_b16f7904bcaaa7a87404cbf85addc7a8645dff94eef4e8ae7182b86e3638e76a =                     // line 159
$context["row"]) && is_array($__internal_b16f7904bcaaa7a87404cbf85addc7a8645dff94eef4e8ae7182b86e3638e76a) || $__internal_b16f7904bcaaa7a87404cbf85addc7a8645dff94eef4e8ae7182b86e3638e76a instanceof ArrayAccess ? ($__internal_b16f7904bcaaa7a87404cbf85addc7a8645dff94eef4e8ae7182b86e3638e76a["Field"] ?? null) : null)))]);
                    // line 160
                    echo "\">
                              ";
                    // line 161
                    echo \PhpMyAdmin\Html\Generator::getIcon("b_unique", _gettext("Unique"));
                    echo "
                            </a>
                          ";
                }
                // line 164
                echo "                        </li>

                        <li class=\"add_index nowrap\">
                          ";
                // line 167
                if ((((($context["type"] ?? null) == "text") || (($context["type"] ?? null) == "blob")) || (($context["tbl_storage_engine"] ?? null) == "ARCHIVE"))) {
                    // line 168
                    echo "                            ";
                    echo \PhpMyAdmin\Html\Generator::getIcon("bd_index", _gettext("Index"));
                    echo "
                          ";
                } else {
                    // line 170
                    echo "                            <a rel=\"samepage\" class=\"ajax add_key print_ignore add_index_anchor\" href=\"";
                    echo PhpMyAdmin\Url::getFromRoute("/table/structure/add-key");
                    echo "\" data-post=\"";
                    echo PhpMyAdmin\Url::getCommon(["db" =>                     // line 171
($context["db"] ?? null), "table" =>                     // line 172
($context["table"] ?? null), "sql_query" => (((("ALTER TABLE " . PhpMyAdmin\Util::backquote(                    // line 173
($context["table"] ?? null))) . " ADD INDEX(") . PhpMyAdmin\Util::backquote((($__internal_462377748602ccf3a44a10ced4240983cec8df1ad86ab53e582fcddddb98fc88 = $context["row"]) && is_array($__internal_462377748602ccf3a44a10ced4240983cec8df1ad86ab53e582fcddddb98fc88) || $__internal_462377748602ccf3a44a10ced4240983cec8df1ad86ab53e582fcddddb98fc88 instanceof ArrayAccess ? ($__internal_462377748602ccf3a44a10ced4240983cec8df1ad86ab53e582fcddddb98fc88["Field"] ?? null) : null))) . ");"), "message_to_show" => sprintf(_gettext("An index has been added on %s."), twig_escape_filter($this->env, (($__internal_be1db6a1ea9fa5c04c40f99df0ec5af053ca391863fc6256c5c4ee249724f758 =                     // line 174
$context["row"]) && is_array($__internal_be1db6a1ea9fa5c04c40f99df0ec5af053ca391863fc6256c5c4ee249724f758) || $__internal_be1db6a1ea9fa5c04c40f99df0ec5af053ca391863fc6256c5c4ee249724f758 instanceof ArrayAccess ? ($__internal_be1db6a1ea9fa5c04c40f99df0ec5af053ca391863fc6256c5c4ee249724f758["Field"] ?? null) : null)))]);
                    // line 175
                    echo "\">
                              ";
                    // line 176
                    echo \PhpMyAdmin\Html\Generator::getIcon("b_index", _gettext("Index"));
                    echo "
                            </a>
                          ";
                }
                // line 179
                echo "                        </li>

                        ";
                // line 181
                $context["spatial_types"] = [0 => "geometry", 1 => "point", 2 => "linestring", 3 => "polygon", 4 => "multipoint", 5 => "multilinestring", 6 => "multipolygon", 7 => "geomtrycollection"];
                // line 191
                echo "                        <li class=\"spatial nowrap\">
                          ";
                // line 192
                if (((((($context["type"] ?? null) == "text") || (($context["type"] ?? null) == "blob")) || (($context["tbl_storage_engine"] ?? null) == "ARCHIVE")) || (!twig_in_filter(($context["type"] ?? null), ($context["spatial_types"] ?? null)) && ((($context["tbl_storage_engine"] ?? null) == "MYISAM") || (($context["mysql_int_version"] ?? null) >= 50705))))) {
                    // line 193
                    echo "                            ";
                    echo \PhpMyAdmin\Html\Generator::getIcon("bd_spatial", _gettext("Spatial"));
                    echo "
                          ";
                } else {
                    // line 195
                    echo "                            <a rel=\"samepage\" class=\"ajax add_key print_ignore add_spatial_anchor\" href=\"";
                    echo PhpMyAdmin\Url::getFromRoute("/table/structure/add-key");
                    echo "\" data-post=\"";
                    echo PhpMyAdmin\Url::getCommon(["db" =>                     // line 196
($context["db"] ?? null), "table" =>                     // line 197
($context["table"] ?? null), "sql_query" => (((("ALTER TABLE " . PhpMyAdmin\Util::backquote(                    // line 198
($context["table"] ?? null))) . " ADD SPATIAL(") . PhpMyAdmin\Util::backquote((($__internal_6e6eda1691934a8f5855a3221f5a9f036391304a5cda73a3a2009f2961a84c35 = $context["row"]) && is_array($__internal_6e6eda1691934a8f5855a3221f5a9f036391304a5cda73a3a2009f2961a84c35) || $__internal_6e6eda1691934a8f5855a3221f5a9f036391304a5cda73a3a2009f2961a84c35 instanceof ArrayAccess ? ($__internal_6e6eda1691934a8f5855a3221f5a9f036391304a5cda73a3a2009f2961a84c35["Field"] ?? null) : null))) . ");"), "message_to_show" => sprintf(_gettext("An index has been added on %s."), twig_escape_filter($this->env, (($__internal_51c633083c79004f3cb5e9e2b2f3504f650f1561800582801028bcbcf733a06b =                     // line 199
$context["row"]) && is_array($__internal_51c633083c79004f3cb5e9e2b2f3504f650f1561800582801028bcbcf733a06b) || $__internal_51c633083c79004f3cb5e9e2b2f3504f650f1561800582801028bcbcf733a06b instanceof ArrayAccess ? ($__internal_51c633083c79004f3cb5e9e2b2f3504f650f1561800582801028bcbcf733a06b["Field"] ?? null) : null)))]);
                    // line 200
                    echo "\">
                              ";
                    // line 201
                    echo \PhpMyAdmin\Html\Generator::getIcon("b_spatial", _gettext("Spatial"));
                    echo "
                            </a>
                          ";
                }
                // line 204
                echo "                        </li>

                        ";
                // line 207
                echo "                        <li class=\"fulltext nowrap\">
                        ";
                // line 208
                if ((( !twig_test_empty(($context["tbl_storage_engine"] ?? null)) && ((((                // line 209
($context["tbl_storage_engine"] ?? null) == "MYISAM") || (                // line 210
($context["tbl_storage_engine"] ?? null) == "ARIA")) || (                // line 211
($context["tbl_storage_engine"] ?? null) == "MARIA")) || ((                // line 212
($context["tbl_storage_engine"] ?? null) == "INNODB") && (($context["mysql_int_version"] ?? null) >= 50604)))) && (twig_in_filter("text",                 // line 213
($context["type"] ?? null)) || twig_in_filter("char", ($context["type"] ?? null))))) {
                    // line 214
                    echo "                            <a rel=\"samepage\" class=\"ajax add_key add_fulltext_anchor\" href=\"";
                    echo PhpMyAdmin\Url::getFromRoute("/table/structure/add-key");
                    echo "\" data-post=\"";
                    echo PhpMyAdmin\Url::getCommon(["db" =>                     // line 215
($context["db"] ?? null), "table" =>                     // line 216
($context["table"] ?? null), "sql_query" => (((("ALTER TABLE " . PhpMyAdmin\Util::backquote(                    // line 217
($context["table"] ?? null))) . " ADD FULLTEXT(") . PhpMyAdmin\Util::backquote((($__internal_064553f1273f2ea50405f85092d06733f3f2fe5d0fc42fda135e1fdc91ff26ae = $context["row"]) && is_array($__internal_064553f1273f2ea50405f85092d06733f3f2fe5d0fc42fda135e1fdc91ff26ae) || $__internal_064553f1273f2ea50405f85092d06733f3f2fe5d0fc42fda135e1fdc91ff26ae instanceof ArrayAccess ? ($__internal_064553f1273f2ea50405f85092d06733f3f2fe5d0fc42fda135e1fdc91ff26ae["Field"] ?? null) : null))) . ");"), "message_to_show" => sprintf(_gettext("An index has been added on %s."), twig_escape_filter($this->env, (($__internal_7bef02f75e2984f8c7fcd4fd7871e286c87c0fdcb248271a136b01ac6dd5dd54 =                     // line 218
$context["row"]) && is_array($__internal_7bef02f75e2984f8c7fcd4fd7871e286c87c0fdcb248271a136b01ac6dd5dd54) || $__internal_7bef02f75e2984f8c7fcd4fd7871e286c87c0fdcb248271a136b01ac6dd5dd54 instanceof ArrayAccess ? ($__internal_7bef02f75e2984f8c7fcd4fd7871e286c87c0fdcb248271a136b01ac6dd5dd54["Field"] ?? null) : null)))]);
                    // line 219
                    echo "\">
                              ";
                    // line 220
                    echo \PhpMyAdmin\Html\Generator::getIcon("b_ftext", _gettext("Fulltext"));
                    echo "
                            </a>
                        ";
                } else {
                    // line 223
                    echo "                          ";
                    echo \PhpMyAdmin\Html\Generator::getIcon("bd_ftext", _gettext("Fulltext"));
                    echo "
                        ";
                }
                // line 225
                echo "                        </li>

                        ";
                // line 228
                echo "                        <li class=\"browse nowrap\">
                            <a href=\"";
                // line 229
                echo PhpMyAdmin\Url::getFromRoute("/sql");
                echo "\" data-post=\"";
                echo PhpMyAdmin\Url::getCommon(["db" =>                 // line 230
($context["db"] ?? null), "table" =>                 // line 231
($context["table"] ?? null), "sql_query" => ((((((((("SELECT COUNT(*) AS " . PhpMyAdmin\Util::backquote(_gettext("Rows"))) . ", ") . PhpMyAdmin\Util::backquote((($__internal_d6ae6b41786cc4be7778386d06cb288c8e6ffd74e055cfed45d7a5c8854d0c8f =                 // line 233
$context["row"]) && is_array($__internal_d6ae6b41786cc4be7778386d06cb288c8e6ffd74e055cfed45d7a5c8854d0c8f) || $__internal_d6ae6b41786cc4be7778386d06cb288c8e6ffd74e055cfed45d7a5c8854d0c8f instanceof ArrayAccess ? ($__internal_d6ae6b41786cc4be7778386d06cb288c8e6ffd74e055cfed45d7a5c8854d0c8f["Field"] ?? null) : null))) . " FROM ") . PhpMyAdmin\Util::backquote(                // line 234
($context["table"] ?? null))) . " GROUP BY ") . PhpMyAdmin\Util::backquote((($__internal_1dcdec7ec31e102fbfe45103ea3599c92c8609311e43d40ca0d95d0369434327 =                 // line 235
$context["row"]) && is_array($__internal_1dcdec7ec31e102fbfe45103ea3599c92c8609311e43d40ca0d95d0369434327) || $__internal_1dcdec7ec31e102fbfe45103ea3599c92c8609311e43d40ca0d95d0369434327 instanceof ArrayAccess ? ($__internal_1dcdec7ec31e102fbfe45103ea3599c92c8609311e43d40ca0d95d0369434327["Field"] ?? null) : null))) . " ORDER BY ") . PhpMyAdmin\Util::backquote((($__internal_891ba2f942018e94e4bfa8069988f305bbaad7f54a64aeee069787f1084a9412 =                 // line 236
$context["row"]) && is_array($__internal_891ba2f942018e94e4bfa8069988f305bbaad7f54a64aeee069787f1084a9412) || $__internal_891ba2f942018e94e4bfa8069988f305bbaad7f54a64aeee069787f1084a9412 instanceof ArrayAccess ? ($__internal_891ba2f942018e94e4bfa8069988f305bbaad7f54a64aeee069787f1084a9412["Field"] ?? null) : null))), "is_browse_distinct" => true]);
                // line 238
                echo "\">
                              ";
                // line 239
                echo \PhpMyAdmin\Html\Generator::getIcon("b_browse", _gettext("Distinct values"));
                echo "
                            </a>
                        </li>
                        ";
                // line 242
                if (($context["central_columns_work"] ?? null)) {
                    // line 243
                    echo "                            <li class=\"browse nowrap\">
                            ";
                    // line 244
                    if (twig_in_filter((($__internal_694b5f53081640f33aab1567e85e28c247e6a7c4674010716df6de8eae4819e9 = $context["row"]) && is_array($__internal_694b5f53081640f33aab1567e85e28c247e6a7c4674010716df6de8eae4819e9) || $__internal_694b5f53081640f33aab1567e85e28c247e6a7c4674010716df6de8eae4819e9 instanceof ArrayAccess ? ($__internal_694b5f53081640f33aab1567e85e28c247e6a7c4674010716df6de8eae4819e9["Field"] ?? null) : null), ($context["central_list"] ?? null))) {
                        // line 245
                        echo "                                <a href=\"#\" class=\"central_columns remove_button\">
                                    ";
                        // line 246
                        echo \PhpMyAdmin\Html\Generator::getIcon("centralColumns_delete", _gettext("Remove from central columns"));
                        echo "
                                </a>
                            ";
                    } else {
                        // line 249
                        echo "                                <a href=\"#\" class=\"central_columns add_button\">
                                    ";
                        // line 250
                        echo \PhpMyAdmin\Html\Generator::getIcon("centralColumns_add", _gettext("Add to central columns"));
                        echo "
                                </a>
                            ";
                    }
                    // line 253
                    echo "                            </li>
                        ";
                }
                // line 255
                echo "                        ";
                if (($context["hide_structure_actions"] ?? null)) {
                    // line 256
                    echo "                                </ul>
                            </li>
                        ";
                }
                // line 259
                echo "                    </ul>
                </td>
            ";
            }
            // line 262
            echo "        </tr>
        ";
        }
        $_parent = $context['_parent'];
        unset($context['_seq'], $context['_iterated'], $context['_key'], $context['row'], $context['_parent'], $context['loop']);
        $context = array_intersect_key($context, $_parent) + $_parent;
        // line 264
        echo "        </tbody>
    </table>
    </div>
    <div class=\"print_ignore\">
        ";
        // line 268
        $this->loadTemplate("select_all.twig", "table/structure/display_structure.twig", 268)->display(twig_to_array(["theme_image_path" =>         // line 269
($context["theme_image_path"] ?? null), "text_dir" =>         // line 270
($context["text_dir"] ?? null), "form_name" => "fieldsForm"]));
        // line 273
        echo "
        <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
        // line 274
        echo PhpMyAdmin\Url::getFromRoute("/table/structure/browse");
        echo "\">
          ";
        // line 275
        echo \PhpMyAdmin\Html\Generator::getIcon("b_browse", _gettext("Browse"));
        echo "
        </button>

        ";
        // line 278
        if (( !($context["tbl_is_view"] ?? null) &&  !($context["db_is_system_schema"] ?? null))) {
            // line 279
            echo "          <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
            echo PhpMyAdmin\Url::getFromRoute("/table/structure/change");
            echo "\">
            ";
            // line 280
            echo \PhpMyAdmin\Html\Generator::getIcon("b_edit", _gettext("Change"));
            echo "
          </button>
          <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
            // line 282
            echo PhpMyAdmin\Url::getFromRoute("/table/structure/drop-confirm");
            echo "\">
            ";
            // line 283
            echo \PhpMyAdmin\Html\Generator::getIcon("b_drop", _gettext("Drop"));
            echo "
          </button>

          ";
            // line 286
            if ((($context["tbl_storage_engine"] ?? null) != "ARCHIVE")) {
                // line 287
                echo "            <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
                echo PhpMyAdmin\Url::getFromRoute("/table/structure/primary");
                echo "\">
              ";
                // line 288
                echo \PhpMyAdmin\Html\Generator::getIcon("b_primary", _gettext("Primary"));
                echo "
            </button>
            <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
                // line 290
                echo PhpMyAdmin\Url::getFromRoute("/table/structure/unique");
                echo "\">
              ";
                // line 291
                echo \PhpMyAdmin\Html\Generator::getIcon("b_unique", _gettext("Unique"));
                echo "
            </button>
            <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
                // line 293
                echo PhpMyAdmin\Url::getFromRoute("/table/structure/index");
                echo "\">
              ";
                // line 294
                echo \PhpMyAdmin\Html\Generator::getIcon("b_index", _gettext("Index"));
                echo "
            </button>
            <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
                // line 296
                echo PhpMyAdmin\Url::getFromRoute("/table/structure/spatial");
                echo "\">
              ";
                // line 297
                echo \PhpMyAdmin\Html\Generator::getIcon("b_spatial", _gettext("Spatial"));
                echo "
            </button>
            <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
                // line 299
                echo PhpMyAdmin\Url::getFromRoute("/table/structure/fulltext");
                echo "\">
              ";
                // line 300
                echo \PhpMyAdmin\Html\Generator::getIcon("b_ftext", _gettext("Fulltext"));
                echo "
            </button>

            ";
                // line 303
                if (($context["central_columns_work"] ?? null)) {
                    // line 304
                    echo "              <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
                    echo PhpMyAdmin\Url::getFromRoute("/table/structure/central-columns-add");
                    echo "\">
                ";
                    // line 305
                    echo \PhpMyAdmin\Html\Generator::getIcon("centralColumns_add", _gettext("Add to central columns"));
                    echo "
              </button>
              <button class=\"btn btn-link mult_submit\" type=\"submit\" formaction=\"";
                    // line 307
                    echo PhpMyAdmin\Url::getFromRoute("/table/structure/central-columns-remove");
                    echo "\">
                ";
                    // line 308
                    echo \PhpMyAdmin\Html\Generator::getIcon("centralColumns_delete", _gettext("Remove from central columns"));
                    echo "
              </button>
            ";
                }
                // line 311
                echo "          ";
            }
            // line 312
            echo "        ";
        }
        // line 313
        echo "    </div>
</form>
<hr class=\"print_ignore\">
<div id=\"move_columns_dialog\" class=\"hide\" title=\"";
        // line 316
        echo _gettext("Move columns");
        echo "\">
    <p>";
        // line 317
        echo _gettext("Move the columns by dragging them up and down.");
        echo "</p>
    <form action=\"";
        // line 318
        echo PhpMyAdmin\Url::getFromRoute("/table/structure/move-columns");
        echo "\" name=\"move_column_form\" id=\"move_column_form\">
        <div>
            ";
        // line 320
        echo PhpMyAdmin\Url::getHiddenInputs(($context["db"] ?? null), ($context["table"] ?? null));
        echo "
            <ul></ul>
        </div>
    </form>
</div>
";
        // line 326
        echo "<div id=\"structure-action-links\">
    ";
        // line 327
        if ((($context["tbl_is_view"] ?? null) &&  !($context["db_is_system_schema"] ?? null))) {
            // line 328
            echo "        ";
            echo PhpMyAdmin\Html\Generator::linkOrButton(PhpMyAdmin\Url::getFromRoute("/view/create", ["db" =>             // line 329
($context["db"] ?? null), "table" => ($context["table"] ?? null)]), \PhpMyAdmin\Html\Generator::getIcon("b_edit", _gettext("Edit view"), true));
            // line 331
            echo "
    ";
        }
        // line 333
        echo "    <a href=\"#\" id=\"printView\">";
        echo \PhpMyAdmin\Html\Generator::getIcon("b_print", _gettext("Print"), true);
        echo "</a>
    ";
        // line 334
        if (( !($context["tbl_is_view"] ?? null) &&  !($context["db_is_system_schema"] ?? null))) {
            // line 335
            echo "        ";
            // line 336
            echo "        ";
            if (((($context["mysql_int_version"] ?? null) < 80000) || ($context["is_mariadb"] ?? null))) {
                // line 337
                echo "          <a class=\"mr-0\" href=\"";
                echo PhpMyAdmin\Url::getFromRoute("/sql");
                echo "\" data-post=\"";
                echo PhpMyAdmin\Url::getCommon(["db" =>                 // line 338
($context["db"] ?? null), "table" =>                 // line 339
($context["table"] ?? null), "sql_query" => (("SELECT * FROM " . PhpMyAdmin\Util::backquote(                // line 340
($context["table"] ?? null))) . " PROCEDURE ANALYSE()"), "session_max_rows" => "all"]);
                // line 342
                echo "\">
            ";
                // line 343
                echo \PhpMyAdmin\Html\Generator::getIcon("b_tblanalyse", _gettext("Propose table structure"), true);
                // line 347
                echo "
          </a>
          ";
                // line 349
                echo \PhpMyAdmin\Html\MySQLDocumentation::show("procedure_analyse");
                echo "
        ";
            }
            // line 351
            echo "        ";
            if (($context["is_active"] ?? null)) {
                // line 352
                echo "            <a href=\"";
                echo PhpMyAdmin\Url::getFromRoute("/table/tracking", ["db" => ($context["db"] ?? null), "table" => ($context["table"] ?? null)]);
                echo "\">
                ";
                // line 353
                echo \PhpMyAdmin\Html\Generator::getIcon("eye", _gettext("Track table"), true);
                echo "
            </a>
        ";
            }
            // line 356
            echo "        <a href=\"#\" id=\"move_columns_anchor\">
            ";
            // line 357
            echo \PhpMyAdmin\Html\Generator::getIcon("b_move", _gettext("Move columns"), true);
            echo "
        </a>
        <a href=\"";
            // line 359
            echo PhpMyAdmin\Url::getFromRoute("/normalization", ["db" => ($context["db"] ?? null), "table" => ($context["table"] ?? null)]);
            echo "\">
            ";
            // line 360
            echo \PhpMyAdmin\Html\Generator::getIcon("normalize", _gettext("Normalize"), true);
            echo "
        </a>
    ";
        }
        // line 363
        echo "    ";
        if ((($context["tbl_is_view"] ?? null) &&  !($context["db_is_system_schema"] ?? null))) {
            // line 364
            echo "        ";
            if (($context["is_active"] ?? null)) {
                // line 365
                echo "            <a href=\"";
                echo PhpMyAdmin\Url::getFromRoute("/table/tracking", ["db" => ($context["db"] ?? null), "table" => ($context["table"] ?? null)]);
                echo "\">
                ";
                // line 366
                echo \PhpMyAdmin\Html\Generator::getIcon("eye", _gettext("Track view"), true);
                echo "
            </a>
        ";
            }
            // line 369
            echo "    ";
        }
        // line 370
        echo "</div>
";
        // line 371
        if (( !($context["tbl_is_view"] ?? null) &&  !($context["db_is_system_schema"] ?? null))) {
            // line 372
            echo "    <form method=\"post\" action=\"";
            echo PhpMyAdmin\Url::getFromRoute("/table/add-field");
            echo "\" id=\"addColumns\" name=\"addColumns\">
        ";
            // line 373
            echo PhpMyAdmin\Url::getHiddenInputs(($context["db"] ?? null), ($context["table"] ?? null));
            echo "
        ";
            // line 374
            if (PhpMyAdmin\Util::showIcons("ActionLinksMode")) {
                // line 375
                echo "            ";
                echo \PhpMyAdmin\Html\Generator::getImage("b_insrow", _gettext("Add column"));
                echo "&nbsp;
        ";
            }
            // line 377
            echo "        ";
            $context["num_fields"] = ('' === $tmp = "<input type=\"number\" name=\"num_fields\" value=\"1\" onfocus=\"this.select()\" min=\"1\" required>") ? '' : new Markup($tmp, $this->env->getCharset());
            // line 380
            echo "        ";
            echo sprintf(_gettext("Add %s column(s)"), ($context["num_fields"] ?? null));
            echo "
        <input type=\"hidden\" name=\"field_where\" value=\"after\">&nbsp;
        ";
            // line 383
            echo "        <select name=\"after_field\">
            <option value=\"first\" data-pos=\"first\">
                ";
            // line 385
            echo _gettext("at beginning of table");
            // line 386
            echo "            </option>
            ";
            // line 387
            $context['_parent'] = $context;
            $context['_seq'] = twig_ensure_traversable(($context["columns_list"] ?? null));
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
            foreach ($context['_seq'] as $context["_key"] => $context["one_column_name"]) {
                // line 388
                echo "                <option value=\"";
                echo twig_escape_filter($this->env, $context["one_column_name"], "html", null, true);
                echo "\"";
                // line 389
                echo (((twig_get_attribute($this->env, $this->source, $context["loop"], "revindex0", [], "any", false, false, false, 389) == 0)) ? (" selected=\"selected\"") : (""));
                echo ">
                    ";
                // line 390
                echo twig_escape_filter($this->env, sprintf(_gettext("after %s"), $context["one_column_name"]), "html", null, true);
                echo "
                </option>
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
            unset($context['_seq'], $context['_iterated'], $context['_key'], $context['one_column_name'], $context['_parent'], $context['loop']);
            $context = array_intersect_key($context, $_parent) + $_parent;
            // line 393
            echo "        </select>
        <input class=\"btn btn-primary\" type=\"submit\" value=\"";
            // line 394
            echo _gettext("Go");
            echo "\">
    </form>
";
        }
        // line 397
        echo "
";
        // line 398
        if ((( !($context["tbl_is_view"] ?? null) &&  !($context["db_is_system_schema"] ?? null)) && (($context["tbl_storage_engine"] ?? null) != "ARCHIVE"))) {
            // line 399
            echo "  <div id=\"index_div\" class=\"w-100 ajax\">
    <fieldset class=\"index_info\">
      <legend id=\"index_header\">
        ";
            // line 402
            echo _gettext("Indexes");
            // line 403
            echo "        ";
            echo \PhpMyAdmin\Html\MySQLDocumentation::show("optimizing-database-structure");
            echo "
      </legend>

      ";
            // line 406
            if ( !twig_test_empty(($context["indexes"] ?? null))) {
                // line 407
                echo "        ";
                echo ($context["indexes_duplicates"] ?? null);
                echo "

        <div class=\"table-responsive jsresponsive\">
          <table class=\"table table-light table-striped table-hover table-sm w-auto\" id=\"table_index\">
            <thead class=\"thead-light\">
              <tr>
                <th colspan=\"3\" class=\"print_ignore\">";
                // line 413
                echo _gettext("Action");
                echo "</th>
                <th>";
                // line 414
                echo _gettext("Keyname");
                echo "</th>
                <th>";
                // line 415
                echo _gettext("Type");
                echo "</th>
                <th>";
                // line 416
                echo _gettext("Unique");
                echo "</th>
                <th>";
                // line 417
                echo _gettext("Packed");
                echo "</th>
                <th>";
                // line 418
                echo _gettext("Column");
                echo "</th>
                <th>";
                // line 419
                echo _gettext("Cardinality");
                echo "</th>
                <th>";
                // line 420
                echo _gettext("Collation");
                echo "</th>
                <th>";
                // line 421
                echo _gettext("Null");
                echo "</th>
                <th>";
                // line 422
                echo _gettext("Comment");
                echo "</th>
              </tr>
            </thead>

            ";
                // line 426
                $context['_parent'] = $context;
                $context['_seq'] = twig_ensure_traversable(($context["indexes"] ?? null));
                foreach ($context['_seq'] as $context["_key"] => $context["index"]) {
                    // line 427
                    echo "              <tbody class=\"row_span\">
                ";
                    // line 428
                    $context["columns_count"] = twig_get_attribute($this->env, $this->source, $context["index"], "getColumnCount", [], "method", false, false, false, 428);
                    // line 429
                    echo "                <tr class=\"noclick\">
                <td rowspan=\"";
                    // line 430
                    echo twig_escape_filter($this->env, ($context["columns_count"] ?? null), "html", null, true);
                    echo "\" class=\"edit_index print_ignore ajax\">
                  <a class=\"ajax\" href=\"";
                    // line 431
                    echo PhpMyAdmin\Url::getFromRoute("/table/indexes");
                    echo "\" data-post=\"";
                    echo PhpMyAdmin\Url::getCommon(["db" =>                     // line 432
($context["db"] ?? null), "table" =>                     // line 433
($context["table"] ?? null), "index" => twig_get_attribute($this->env, $this->source,                     // line 434
$context["index"], "getName", [], "method", false, false, false, 434)], "");
                    // line 435
                    echo "\">
                    ";
                    // line 436
                    echo \PhpMyAdmin\Html\Generator::getIcon("b_edit", _gettext("Edit"));
                    echo "
                  </a>
                </td>
                <td rowspan=\"";
                    // line 439
                    echo twig_escape_filter($this->env, ($context["columns_count"] ?? null), "html", null, true);
                    echo "\" class=\"rename_index print_ignore ajax\" >
                  <a class=\"ajax\" href=\"";
                    // line 440
                    echo PhpMyAdmin\Url::getFromRoute("/table/indexes/rename");
                    echo "\" data-post=\"";
                    echo PhpMyAdmin\Url::getCommon(["db" =>                     // line 441
($context["db"] ?? null), "table" =>                     // line 442
($context["table"] ?? null), "index" => twig_get_attribute($this->env, $this->source,                     // line 443
$context["index"], "getName", [], "method", false, false, false, 443)], "");
                    // line 444
                    echo "\">
                    ";
                    // line 445
                    echo \PhpMyAdmin\Html\Generator::getIcon("b_rename", _gettext("Rename"));
                    echo "
                  </a>
                </td>
                <td rowspan=\"";
                    // line 448
                    echo twig_escape_filter($this->env, ($context["columns_count"] ?? null), "html", null, true);
                    echo "\" class=\"print_ignore\">
                  ";
                    // line 449
                    if ((twig_get_attribute($this->env, $this->source, $context["index"], "getName", [], "method", false, false, false, 449) == "PRIMARY")) {
                        // line 450
                        echo "                    ";
                        $context["index_params"] = ["sql_query" => (("ALTER TABLE " . PhpMyAdmin\Util::backquote(                        // line 451
($context["table"] ?? null))) . " DROP PRIMARY KEY;"), "message_to_show" => _gettext("The primary key has been dropped.")];
                        // line 454
                        echo "                  ";
                    } else {
                        // line 455
                        echo "                    ";
                        $context["index_params"] = ["sql_query" => (((("ALTER TABLE " . PhpMyAdmin\Util::backquote(                        // line 456
($context["table"] ?? null))) . " DROP INDEX ") . PhpMyAdmin\Util::backquote(twig_get_attribute($this->env, $this->source, $context["index"], "getName", [], "method", false, false, false, 456))) . ";"), "message_to_show" => sprintf(_gettext("Index %s has been dropped."), twig_get_attribute($this->env, $this->source,                         // line 457
$context["index"], "getName", [], "method", false, false, false, 457))];
                        // line 459
                        echo "                  ";
                    }
                    // line 460
                    echo "
                  <input type=\"hidden\" class=\"drop_primary_key_index_msg\" value=\"";
                    // line 461
                    echo PhpMyAdmin\Sanitize::jsFormat(twig_get_attribute($this->env, $this->source, ($context["index_params"] ?? null), "sql_query", [], "any", false, false, false, 461), false);
                    echo "\">
                  ";
                    // line 462
                    echo PhpMyAdmin\Html\Generator::linkOrButton(PhpMyAdmin\Url::getFromRoute("/sql", twig_array_merge(                    // line 463
($context["index_params"] ?? null), ["db" => ($context["db"] ?? null), "table" => ($context["table"] ?? null)])), \PhpMyAdmin\Html\Generator::getIcon("b_drop", _gettext("Drop")), ["class" => "drop_primary_key_index_anchor ajax"]);
                    // line 466
                    echo "
                </td>
                <th rowspan=\"";
                    // line 468
                    echo twig_escape_filter($this->env, ($context["columns_count"] ?? null), "html", null, true);
                    echo "\">";
                    echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["index"], "getName", [], "method", false, false, false, 468), "html", null, true);
                    echo "</th>
                <td rowspan=\"";
                    // line 469
                    echo twig_escape_filter($this->env, ($context["columns_count"] ?? null), "html", null, true);
                    echo "\">";
                    echo twig_escape_filter($this->env, ((twig_get_attribute($this->env, $this->source, $context["index"], "getType", [], "method", true, true, false, 469)) ? (_twig_default_filter(twig_get_attribute($this->env, $this->source, $context["index"], "getType", [], "method", false, false, false, 469), twig_get_attribute($this->env, $this->source, $context["index"], "getChoice", [], "method", false, false, false, 469))) : (twig_get_attribute($this->env, $this->source, $context["index"], "getChoice", [], "method", false, false, false, 469))), "html", null, true);
                    echo "</td>
                <td rowspan=\"";
                    // line 470
                    echo twig_escape_filter($this->env, ($context["columns_count"] ?? null), "html", null, true);
                    echo "\">";
                    echo twig_escape_filter($this->env, ((twig_get_attribute($this->env, $this->source, $context["index"], "isUnique", [], "method", false, false, false, 470)) ? (_gettext("Yes")) : (_gettext("No"))), "html", null, true);
                    echo "</td>
                <td rowspan=\"";
                    // line 471
                    echo twig_escape_filter($this->env, ($context["columns_count"] ?? null), "html", null, true);
                    echo "\">";
                    echo twig_get_attribute($this->env, $this->source, $context["index"], "isPacked", [], "method", false, false, false, 471);
                    echo "</td>

                ";
                    // line 473
                    $context['_parent'] = $context;
                    $context['_seq'] = twig_ensure_traversable(twig_get_attribute($this->env, $this->source, $context["index"], "getColumns", [], "method", false, false, false, 473));
                    foreach ($context['_seq'] as $context["_key"] => $context["column"]) {
                        // line 474
                        echo "                  ";
                        if ((twig_get_attribute($this->env, $this->source, $context["column"], "getSeqInIndex", [], "method", false, false, false, 474) > 1)) {
                            // line 475
                            echo "                    <tr class=\"noclick\">
                  ";
                        }
                        // line 477
                        echo "                  <td>
                    ";
                        // line 478
                        echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["column"], "getName", [], "method", false, false, false, 478), "html", null, true);
                        echo "
                    ";
                        // line 479
                        if ( !twig_test_empty(twig_get_attribute($this->env, $this->source, $context["column"], "getSubPart", [], "method", false, false, false, 479))) {
                            // line 480
                            echo "                      (";
                            echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["column"], "getSubPart", [], "method", false, false, false, 480), "html", null, true);
                            echo ")
                    ";
                        }
                        // line 482
                        echo "                  </td>
                  <td>";
                        // line 483
                        echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["column"], "getCardinality", [], "method", false, false, false, 483), "html", null, true);
                        echo "</td>
                  <td>";
                        // line 484
                        echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["column"], "getCollation", [], "method", false, false, false, 484), "html", null, true);
                        echo "</td>
                  <td>";
                        // line 485
                        echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["column"], "getNull", [0 => true], "method", false, false, false, 485), "html", null, true);
                        echo "</td>

                  ";
                        // line 487
                        if ((twig_get_attribute($this->env, $this->source, $context["column"], "getSeqInIndex", [], "method", false, false, false, 487) == 1)) {
                            // line 488
                            echo "                    <td rowspan=\"";
                            echo twig_escape_filter($this->env, ($context["columns_count"] ?? null), "html", null, true);
                            echo "\">";
                            echo twig_escape_filter($this->env, twig_get_attribute($this->env, $this->source, $context["index"], "getComments", [], "method", false, false, false, 488), "html", null, true);
                            echo "</td>
                  ";
                        }
                        // line 490
                        echo "                  </tr>
                ";
                    }
                    $_parent = $context['_parent'];
                    unset($context['_seq'], $context['_iterated'], $context['_key'], $context['column'], $context['_parent'], $context['loop']);
                    $context = array_intersect_key($context, $_parent) + $_parent;
                    // line 492
                    echo "              </tbody>
            ";
                }
                $_parent = $context['_parent'];
                unset($context['_seq'], $context['_iterated'], $context['_key'], $context['index'], $context['_parent'], $context['loop']);
                $context = array_intersect_key($context, $_parent) + $_parent;
                // line 494
                echo "          </table>
        </div>
      ";
            } else {
                // line 497
                echo "        <div class=\"no_indexes_defined\">";
                echo call_user_func_array($this->env->getFilter('notice')->getCallable(), [_gettext("No index defined!")]);
                echo "</div>
      ";
            }
            // line 499
            echo "    </fieldset>

    <fieldset class=\"tblFooters print_ignore text-left\">
      <form action=\"";
            // line 502
            echo PhpMyAdmin\Url::getFromRoute("/table/indexes");
            echo "\" method=\"post\">
        ";
            // line 503
            echo PhpMyAdmin\Url::getHiddenInputs(($context["db"] ?? null), ($context["table"] ?? null));
            echo "
        <input type=\"hidden\" name=\"create_index\" value=\"1\">

        ";
            // line 506
            ob_start(function () { return ''; });
            // line 507
            echo "          ";
            echo _gettext("Create an index on %s columns");
            // line 508
            echo "        ";
            $___internal_4e756e983cbb281e119719f6904a4291ed2e6fe4867a6dc96d217be1a49381b2_ = ('' === $tmp = ob_get_clean()) ? '' : new Markup($tmp, $this->env->getCharset());
            // line 506
            echo sprintf($___internal_4e756e983cbb281e119719f6904a4291ed2e6fe4867a6dc96d217be1a49381b2_, "<input class=\"mx-2\" type=\"number\" name=\"added_fields\" value=\"1\" min=\"1\" required>");
            // line 509
            echo "
        <input class=\"btn btn-primary add_index ajax\" type=\"submit\" value=\"";
            // line 510
            echo _gettext("Go");
            echo "\">
      </form>
    </fieldset>
  </div>
";
        }
        // line 515
        echo "
";
        // line 517
        if (($context["have_partitioning"] ?? null)) {
            // line 518
            echo "    ";
            // line 519
            echo "    ";
            if (( !twig_test_empty(($context["partition_names"] ?? null)) &&  !(null === (($__internal_91b272a21580197773f482962c8b92637a641a749832ee390d7d386a58d1912e = ($context["partition_names"] ?? null)) && is_array($__internal_91b272a21580197773f482962c8b92637a641a749832ee390d7d386a58d1912e) || $__internal_91b272a21580197773f482962c8b92637a641a749832ee390d7d386a58d1912e instanceof ArrayAccess ? ($__internal_91b272a21580197773f482962c8b92637a641a749832ee390d7d386a58d1912e[0] ?? null) : null)))) {
                // line 520
                echo "        ";
                $context["first_partition"] = (($__internal_7f8d0071642f16d6b4720f8eef58ffd71faf0c4d7a772c0eb6842d5e9d901ca5 = ($context["partitions"] ?? null)) && is_array($__internal_7f8d0071642f16d6b4720f8eef58ffd71faf0c4d7a772c0eb6842d5e9d901ca5) || $__internal_7f8d0071642f16d6b4720f8eef58ffd71faf0c4d7a772c0eb6842d5e9d901ca5 instanceof ArrayAccess ? ($__internal_7f8d0071642f16d6b4720f8eef58ffd71faf0c4d7a772c0eb6842d5e9d901ca5[0] ?? null) : null);
                // line 521
                echo "        ";
                $context["range_or_list"] = ((((twig_get_attribute($this->env, $this->source, ($context["first_partition"] ?? null), "getMethod", [], "method", false, false, false, 521) == "RANGE") || (twig_get_attribute($this->env, $this->source,                 // line 522
($context["first_partition"] ?? null), "getMethod", [], "method", false, false, false, 522) == "RANGE COLUMNS")) || (twig_get_attribute($this->env, $this->source,                 // line 523
($context["first_partition"] ?? null), "getMethod", [], "method", false, false, false, 523) == "LIST")) || (twig_get_attribute($this->env, $this->source,                 // line 524
($context["first_partition"] ?? null), "getMethod", [], "method", false, false, false, 524) == "LIST COLUMNS"));
                // line 525
                echo "        ";
                $context["sub_partitions"] = twig_get_attribute($this->env, $this->source, ($context["first_partition"] ?? null), "getSubPartitions", [], "method", false, false, false, 525);
                // line 526
                echo "        ";
                $context["has_sub_partitions"] = twig_get_attribute($this->env, $this->source, ($context["first_partition"] ?? null), "hasSubPartitions", [], "method", false, false, false, 526);
                // line 527
                echo "        ";
                if (($context["has_sub_partitions"] ?? null)) {
                    // line 528
                    echo "            ";
                    $context["first_sub_partition"] = (($__internal_0aa0713b35e28227396d65db75a1a4277b081ff4e08585143330919af9d1bf0a = ($context["sub_partitions"] ?? null)) && is_array($__internal_0aa0713b35e28227396d65db75a1a4277b081ff4e08585143330919af9d1bf0a) || $__internal_0aa0713b35e28227396d65db75a1a4277b081ff4e08585143330919af9d1bf0a instanceof ArrayAccess ? ($__internal_0aa0713b35e28227396d65db75a1a4277b081ff4e08585143330919af9d1bf0a[0] ?? null) : null);
                    // line 529
                    echo "        ";
                }
                // line 530
                echo "
        <div id=\"partitions-2\"";
                // line 531
                if ((($context["default_sliders_state"] ?? null) != "disabled")) {
                    // line 532
                    echo (((($context["default_sliders_state"] ?? null) == "closed")) ? (" style=\"display: none; overflow:auto;\"") : (""));
                    echo " class=\"pma_auto_slider\" title=\"";
                    echo _gettext("Partitions");
                    echo "\"";
                }
                // line 533
                echo ">

        ";
                // line 535
                $this->loadTemplate("table/structure/display_partitions.twig", "table/structure/display_structure.twig", 535)->display(twig_to_array(["db" =>                 // line 536
($context["db"] ?? null), "table" =>                 // line 537
($context["table"] ?? null), "partitions" =>                 // line 538
($context["partitions"] ?? null), "partition_method" => twig_get_attribute($this->env, $this->source,                 // line 539
($context["first_partition"] ?? null), "getMethod", [], "method", false, false, false, 539), "partition_expression" => twig_get_attribute($this->env, $this->source,                 // line 540
($context["first_partition"] ?? null), "getExpression", [], "method", false, false, false, 540), "has_description" =>  !twig_test_empty(twig_get_attribute($this->env, $this->source,                 // line 541
($context["first_partition"] ?? null), "getDescription", [], "method", false, false, false, 541)), "has_sub_partitions" =>                 // line 542
($context["has_sub_partitions"] ?? null), "sub_partition_method" => ((                // line 543
($context["has_sub_partitions"] ?? null)) ? (twig_get_attribute($this->env, $this->source, ($context["first_sub_partition"] ?? null), "getMethod", [], "method", false, false, false, 543)) : ("")), "sub_partition_expression" => ((                // line 544
($context["has_sub_partitions"] ?? null)) ? (twig_get_attribute($this->env, $this->source, ($context["first_sub_partition"] ?? null), "getExpression", [], "method", false, false, false, 544)) : ("")), "range_or_list" =>                 // line 545
($context["range_or_list"] ?? null)]));
                // line 547
                echo "    ";
            } else {
                // line 548
                echo "        ";
                $this->loadTemplate("table/structure/display_partitions.twig", "table/structure/display_structure.twig", 548)->display(twig_to_array(["db" =>                 // line 549
($context["db"] ?? null), "table" =>                 // line 550
($context["table"] ?? null)]));
                // line 552
                echo "    ";
            }
            // line 553
            echo "    </div>
";
        }
        // line 555
        echo "
";
        // line 557
        if (($context["show_stats"] ?? null)) {
            // line 558
            echo "    ";
            echo ($context["table_stats"] ?? null);
            echo "
";
        }
        // line 560
        echo "<div class=\"clearfloat\"></div>
";
    }

    public function getTemplateName()
    {
        return "table/structure/display_structure.twig";
    }

    public function isTraitable()
    {
        return false;
    }

    public function getDebugInfo()
    {
        return array (  1335 => 560,  1329 => 558,  1327 => 557,  1324 => 555,  1320 => 553,  1317 => 552,  1315 => 550,  1314 => 549,  1312 => 548,  1309 => 547,  1307 => 545,  1306 => 544,  1305 => 543,  1304 => 542,  1303 => 541,  1302 => 540,  1301 => 539,  1300 => 538,  1299 => 537,  1298 => 536,  1297 => 535,  1293 => 533,  1287 => 532,  1285 => 531,  1282 => 530,  1279 => 529,  1276 => 528,  1273 => 527,  1270 => 526,  1267 => 525,  1265 => 524,  1264 => 523,  1263 => 522,  1261 => 521,  1258 => 520,  1255 => 519,  1253 => 518,  1251 => 517,  1248 => 515,  1240 => 510,  1237 => 509,  1235 => 506,  1232 => 508,  1229 => 507,  1227 => 506,  1221 => 503,  1217 => 502,  1212 => 499,  1206 => 497,  1201 => 494,  1194 => 492,  1187 => 490,  1179 => 488,  1177 => 487,  1172 => 485,  1168 => 484,  1164 => 483,  1161 => 482,  1155 => 480,  1153 => 479,  1149 => 478,  1146 => 477,  1142 => 475,  1139 => 474,  1135 => 473,  1128 => 471,  1122 => 470,  1116 => 469,  1110 => 468,  1106 => 466,  1104 => 463,  1103 => 462,  1099 => 461,  1096 => 460,  1093 => 459,  1091 => 457,  1090 => 456,  1088 => 455,  1085 => 454,  1083 => 451,  1081 => 450,  1079 => 449,  1075 => 448,  1069 => 445,  1066 => 444,  1064 => 443,  1063 => 442,  1062 => 441,  1059 => 440,  1055 => 439,  1049 => 436,  1046 => 435,  1044 => 434,  1043 => 433,  1042 => 432,  1039 => 431,  1035 => 430,  1032 => 429,  1030 => 428,  1027 => 427,  1023 => 426,  1016 => 422,  1012 => 421,  1008 => 420,  1004 => 419,  1000 => 418,  996 => 417,  992 => 416,  988 => 415,  984 => 414,  980 => 413,  970 => 407,  968 => 406,  961 => 403,  959 => 402,  954 => 399,  952 => 398,  949 => 397,  943 => 394,  940 => 393,  923 => 390,  919 => 389,  915 => 388,  898 => 387,  895 => 386,  893 => 385,  889 => 383,  883 => 380,  880 => 377,  874 => 375,  872 => 374,  868 => 373,  863 => 372,  861 => 371,  858 => 370,  855 => 369,  849 => 366,  844 => 365,  841 => 364,  838 => 363,  832 => 360,  828 => 359,  823 => 357,  820 => 356,  814 => 353,  809 => 352,  806 => 351,  801 => 349,  797 => 347,  795 => 343,  792 => 342,  790 => 340,  789 => 339,  788 => 338,  784 => 337,  781 => 336,  779 => 335,  777 => 334,  772 => 333,  768 => 331,  766 => 329,  764 => 328,  762 => 327,  759 => 326,  751 => 320,  746 => 318,  742 => 317,  738 => 316,  733 => 313,  730 => 312,  727 => 311,  721 => 308,  717 => 307,  712 => 305,  707 => 304,  705 => 303,  699 => 300,  695 => 299,  690 => 297,  686 => 296,  681 => 294,  677 => 293,  672 => 291,  668 => 290,  663 => 288,  658 => 287,  656 => 286,  650 => 283,  646 => 282,  641 => 280,  636 => 279,  634 => 278,  628 => 275,  624 => 274,  621 => 273,  619 => 270,  618 => 269,  617 => 268,  611 => 264,  604 => 262,  599 => 259,  594 => 256,  591 => 255,  587 => 253,  581 => 250,  578 => 249,  572 => 246,  569 => 245,  567 => 244,  564 => 243,  562 => 242,  556 => 239,  553 => 238,  551 => 236,  550 => 235,  549 => 234,  548 => 233,  547 => 231,  546 => 230,  543 => 229,  540 => 228,  536 => 225,  530 => 223,  524 => 220,  521 => 219,  519 => 218,  518 => 217,  517 => 216,  516 => 215,  512 => 214,  510 => 213,  509 => 212,  508 => 211,  507 => 210,  506 => 209,  505 => 208,  502 => 207,  498 => 204,  492 => 201,  489 => 200,  487 => 199,  486 => 198,  485 => 197,  484 => 196,  480 => 195,  474 => 193,  472 => 192,  469 => 191,  467 => 181,  463 => 179,  457 => 176,  454 => 175,  452 => 174,  451 => 173,  450 => 172,  449 => 171,  445 => 170,  439 => 168,  437 => 167,  432 => 164,  426 => 161,  423 => 160,  421 => 159,  420 => 158,  419 => 157,  418 => 156,  414 => 155,  408 => 153,  406 => 152,  401 => 149,  395 => 146,  392 => 145,  390 => 144,  389 => 143,  388 => 142,  387 => 141,  383 => 140,  377 => 138,  375 => 137,  371 => 135,  365 => 132,  362 => 131,  360 => 130,  356 => 128,  353 => 127,  351 => 126,  348 => 125,  341 => 121,  338 => 120,  336 => 119,  335 => 117,  334 => 116,  333 => 115,  332 => 114,  329 => 113,  322 => 109,  319 => 108,  317 => 106,  316 => 105,  315 => 104,  314 => 103,  311 => 102,  309 => 101,  304 => 100,  298 => 97,  295 => 96,  293 => 95,  290 => 94,  284 => 92,  280 => 90,  277 => 89,  271 => 87,  265 => 85,  262 => 84,  260 => 83,  255 => 81,  251 => 80,  248 => 79,  240 => 77,  238 => 76,  233 => 73,  225 => 71,  223 => 70,  222 => 69,  218 => 68,  213 => 66,  206 => 63,  200 => 61,  192 => 59,  190 => 58,  186 => 57,  181 => 55,  174 => 53,  169 => 50,  167 => 49,  164 => 48,  162 => 47,  159 => 46,  157 => 45,  154 => 44,  151 => 43,  146 => 42,  143 => 41,  138 => 37,  132 => 35,  129 => 34,  126 => 33,  121 => 31,  116 => 29,  114 => 28,  110 => 27,  106 => 26,  102 => 25,  98 => 24,  94 => 23,  90 => 22,  84 => 18,  79 => 14,  76 => 13,  73 => 11,  71 => 10,  69 => 9,  67 => 8,  63 => 6,  59 => 5,  55 => 4,  50 => 3,  46 => 2,  35 => 1,);
    }

    public function getSourceContext()
    {
        return new Source("", "table/structure/display_structure.twig", "C:\\xampp\\phpMyAdmin\\templates\\table\\structure\\display_structure.twig");
    }
}
