//
// Created by Garry Morrison on 20/11/2020.
//

#include "OperatorUsageMap.h"

OperatorUsageMap operator_usage_map;

OperatorUsageMap::OperatorUsageMap() {
    operator_usage_map.map["empty"] =
            "\nempty:\n"
            "    description:\n\n"
            "    examples:\n\n"
            "    see also:\n";

    operator_usage_map.map["clean"] =
            "\nclean:\n"
            "    description:\n"
            "        clean ket\n"
            "        clean the coefficients of the given superposition\n"
            "        if x < 0, return 0, else return 1\n"
            "        The combination: drop clean sp\n"
            "        converts the given superposition into a \"clean\" superposition\n\n"
            "    examples:\n"
            "        -- clean a superposition:\n"
            "        clean (3|a> + 2.2|b> - 3 |c> + |d>)\n"
            "            |a> + |b> + 0|c> + |d>\n\n"
            "        -- generate a \"clean\" superposition from an arbitrary superposition:\n"
            "        drop clean (3|a> + 2.2|b> - 3 |c> + |d>)\n"
            "            |a> + |b> + |d>\n\n"
            "    see also:\n"
            "        drop\n";

    operator_usage_map.map["drop"] =
            "\ndrop:\n"
            "    description:\n"
            "        drop sp\n"
            "        drop all kets with coeff <= 0 from the given superposition\n\n"
            "    examples:\n"
            "        drop (|a> + 0|b> - 2|c> + 7.1|d>)\n"
            "            |a> + 7.100000|d>\n\n"
            "    see also:\n"
            "        drop-below, drop-above, sdrop\n";

    operator_usage_map.map["filter"] =
            "\nfilter:\n"
            "    description:\n"
            "        filter(operators, conditions) input-seq\n"
            "        Filters the input sequence to only those elements that satisfy the operator/condition pair\n"
            "        It is more powerful than the such-that[] operator\n"
            "        Currently input-seq is converted to superposition, so sequence structure is ignored\n"
            "        Will probably change this behaviour later\n\n"
            "    examples:\n"
            "        -- learn some knowledge\n"
            "        is-food |bread> => |yes>\n"
            "        is-food |cheese> => |yes>\n"
            "        is-food |steak> => |yes>\n\n"
            "        is-furniture |chair> => |yes>\n"
            "        is-furniture |table> => |yes>\n"
            "        is-furniture |stool> => |yes>\n"
            "        is-furniture |lounge> => |yes>\n\n"
            "        is-day-of-week |monday> => |yes>\n"
            "        is-day-of-week |tuesday> => |yes>\n"
            "        is-day-of-week |wednesday> => |yes>\n"
            "        is-day-of-week |thursday> => |yes>\n"
            "        is-day-of-week |friday> => |yes>\n"
            "        is-day-of-week |saturday> => |yes>\n"
            "        is-day-of-week |sunday> => |yes>\n\n"
            "        -- now try some filters:\n"
            "        -- filter all known kets to those that are furniture:\n"
            "        filter(|op: is-furniture>, |yes>) rel-kets[*]\n"
            "            |chair> + |table> + |stool> + |lounge>\n\n"
            "        -- filter all known kets to those that are food:\n"
            "        filter(|op: is-food>, |yes>) rel-kets[*]\n"
            "            |bread> + |cheese> + |steak>\n\n"
            "        -- filter all known kets to those that are days of the week:\n"
            "        filter(|op: is-day-of-week>, |yes>) rel-kets[*]\n"
            "            |monday> + |tuesday> + |wednesday> + |thursday> + |friday> + |saturday> + |sunday>\n\n\n"
            "        -- an indirect filter example, first learn some knowledge:\n"
            "        father |John> => |Fred>\n"
            "        occupation |Fred> => |politician>\n\n"
            "        father |Sam> => |Robert>\n"
            "        occupation |Robert> => |doctor>\n\n"
            "        father |Emma> => |Jack>\n"
            "        occupation |Jack> => |nurse>\n\n"
            "        -- find people that have a father with occupation nurse:\n"
            "        -- NB: Note the ops: rather than op: to signify operator sequence rather than just an operator\n"
            "        filter(|ops: occupation father>, |nurse>) rel-kets[*]\n"
            "            |Emma>\n\n"
            "        -- find people that have a father with occupation doctor:\n"
            "        filter(|ops: occupation father>, |doctor>) rel-kets[*]\n"
            "            |Sam>\n\n\n"
            "        -- find people that have the father operator defined:\n"
            "        -- which is very close in function to the rel-kets[father] operator\n"
            "        filter(|op: father>, |*>) rel-kets[*]\n"
            "            |John> + |Sam> + |Emma>\n\n"
            "        -- filter to people that have a father with occupation of either doctor or nurse:\n"
            "        filter(|ops: occupation father>, |doctor> + |nurse>) rel-kets[*]\n"
            "            |Sam> + |Emma>\n\n"
            "        -- filter to those that have a rule of any type that is doctor or nurse:\n"
            "        -- NB: if rel-kets[*] is large, or supported-ops is large, this may be slow.\n"
            "        filter(|*>, |doctor> + |nurse>) rel-kets[*]\n"
            "            |Robert> + |Jack>\n\n\n"
            "        -- Finally, filters can be easily chained.\n"
            "        -- Eg, To find all kets that are human, American and are politicians:\n"
            "        -- NB: will be faster if you apply the most strict condition(s) first.\n"
            "        -- Eg, in this case, politician first, then American, then human.\n"
            "        filter(|op: is-human>, |yes>) filter(|op: is-american>, |yes>) filter(|op: occupation>, |politician>) rel-kets[*]\n\n"
            "    see also:\n\n"
            "    TODO:\n"
            "        preserve sequence structure of input-seq, currently it is cast to superposition\n"
            "        currently coefficients of kets are ignored, maybe they should be preserved";

    operator_usage_map.map["apply"] =
            "\napply:\n"
            "    description:\n"
            "        apply(seq, seq)\n"
            "        wrapper around apply op\n\n"
            "    examples:\n"
            "        -- learn some knowledge\n"
            "        age |Fred> => |35>\n"
            "        nick-name |Fred> => |Freddie>\n"
            "        mother |Fred> => |Jude>\n"
            "        father |Fred> => |Tom>\n"
            "        age |Jude> => |61>\n\n"
            "        -- implements: age |Fred>\n"
            "        apply(|op: age>, |Fred>)\n"
            "            |35>\n\n"
            "        -- implements: age |Fred> + mother |Fred> + father |Fred>\n"
            "        apply(|op: age> + |op: mother> + |op: father>, |Fred>)\n"
            "            |35> + |Jude> + |Tom>\n\n"
            "        -- implements: age |Fred> . mother |Fred> . father |Fred>\n"
            "        apply(|op: age> . |op: mother> . |op: father>, |Fred>)\n"
            "            |35> . |Jude> . |Tom>\n\n"
            "        -- the star operator, which adds all the right hand rules together:\n"
            "        star |*> #=> apply(supported-ops|_self>, |_self>) |>\n\n"
            "        -- Eg, applied to Fred:\n"
            "        star |Fred>\n"
            "            |35> + |Freddie> + |Jude> + |Tom>\n\n"
            "        -- using an operator sequence instead:\n"
            "        -- implements: age mother |Fred>\n"
            "        apply(|ops: age mother>, |Fred>)\n"
            "            |61>\n\n"
            "    see also:\n"
            "        learn, add-learn, seq-learn";

    operator_usage_map.map["learn"] =
            "\nlearn:\n"
            "    description:\n"
            "        learn(sp, sp, seq)\n"
            "        wrapper around a learn rule\n\n"
            "    examples:\n"
            "        -- implements: age |Fred> => |37>\n"
            "        learn(|op: age>, |Fred>, |37>)\n\n"
            "    see also:\n"
            "         add-learn, seq-learn, apply";

    operator_usage_map.map["add-learn"] =
            "\nadd-learn:\n"
            "    description:\n"
            "        add-learn(sp, sp, seq)\n"
            "        wrapper around an add-learn rule\n\n"
            "    examples:\n"
            "        -- implements: friend |Fred> +=> |Sam>\n"
            "        -- implements: friend |Fred> +=> |Emma>\n"
            "        add-learn(|op: friend>, |Fred>, |Sam>)\n"
            "        add-learn(|op: friend>, |Fred>, |Emma>)\n\n"
            "    see also:\n"
            "         learn, seq-learn, apply";

    operator_usage_map.map["seq-learn"] =
            "\nseq-learn:\n"
            "    description:\n"
            "        seq-learn(sp, sp, seq)\n"
            "        wrapper around a seq-learn rule\n\n"
            "    examples:\n"
            "        -- implements: friend |Fred> .=> |Sam>\n"
            "        -- implements: friend |Fred> .=> |Emma>\n"
            "        seq-learn(|op: friend>, |Fred>, |Sam>)\n"
            "        seq-learn(|op: friend>, |Fred>, |Emma>)\n\n"
            "    see also:\n"
            "         learn, add-learn, apply";

    operator_usage_map.map["smerge"] =
            "\nsmerge:\n"
            "    description:\n"
            "        smerge seq\n"
            "        smerge[\"str\"] seq\n"
            "        merges a sequence into a single string, optionally separated by the str string\n\n"
            "    examples:\n"
            "        smerge (|F> . |r> . |e> . |d>)\n"
            "            |Fred>\n\n"
            "        smerge[\", \"] (|a> . |b> . |c> . |d>)\n"
            "            |a, b, c, d>\n\n"
            "        -- define the bracket operator:\n"
            "        bracket (*) #=> |[> _ smerge[\", \"] |__self> _ |]>\n\n"
            "        -- define the print-bracket operator:\n"
            "        print-bracket (*) #=> print bracket |__self>\n\n"
            "        -- quick test of the bracket operator:\n"
            "        bracket (|F> . |r> . |e> . |d>)\n"
            "            |[F, r, e, d]>\n\n"
            "        -- quick test of the print-bracket operator:\n"
            "        print-bracket (|F> . |r> . |e> . |d>)\n"
            "            [F, r, e, d]\n"
            "            |[F, r, e, d]>\n\n"
            "    see also:\n"
            "        ssplit, smap";

    operator_usage_map.map["learn-grid"] =
            "\nlearn-grid:\n"
            "    description:\n"
            "        learn-grid[width, height]\n"
            "        learn-grid[width, height, operator]\n"
            "        learn a grid of specified width and height\n"
            "        all cells initialized to zero, with respect to operator \"operator\"\n"
            "        if operator is not specified, use \"value\"\n"
            "        and we learn all direction operators, N, NE, E, SE, S, SW, W, NW, that don't point outside the grid\n\n"
            "    examples:\n"
            "        -- learn a sample grid:\n"
            "        learn-grid[2,2]\n"
            "        dump\n"
            "        ------------------------------------------\n"
            "        |context> => |Global context>\n"
            "\n"
            "        value |grid: 0: 0> => |0>\n"
            "        E |grid: 0: 0> => |grid: 0: 1>\n"
            "        SE |grid: 0: 0> => |grid: 1: 1>\n"
            "        S |grid: 0: 0> => |grid: 1: 0>\n"
            "\n"
            "        value |grid: 0: 1> => |0>\n"
            "        S |grid: 0: 1> => |grid: 1: 1>\n"
            "        SW |grid: 0: 1> => |grid: 1: 0>\n"
            "        W |grid: 0: 1> => |grid: 0: 0>\n"
            "\n"
            "        value |grid: 1: 0> => |0>\n"
            "        N |grid: 1: 0> => |grid: 0: 0>\n"
            "        NE |grid: 1: 0> => |grid: 0: 1>\n"
            "        E |grid: 1: 0> => |grid: 1: 1>\n"
            "\n"
            "        value |grid: 1: 1> => |0>\n"
            "        N |grid: 1: 1> => |grid: 0: 1>\n"
            "        W |grid: 1: 1> => |grid: 1: 0>\n"
            "        NW |grid: 1: 1> => |grid: 0: 0>\n"
            "        ------------------------------------------\n\n"
            "    see also:\n"
            "        display-grid";

    operator_usage_map.map["display-grid"] =
            "\ndisplay-grid:\n"
            "    description:\n"
            "        display-grid[width, height]\n"
            "        display-grid[width, height, operator]\n"
            "        display-grid[width, height, operator, empty-char]\n"
            "        display a rectangular map of the given width and height\n"
            "        where each cell is the value of \"operator\" applied to that cell (default operator is \"value\")\n"
            "        where empty-char is printed for cells with value 0 (default value of empty-char is \".\")\n\n"
            "    examples:\n"
            "        -- learn a small grid first:\n"
            "        learn-grid[9,5]\n\n"
            "        -- learn some cell values:\n"
            "        value |grid: 2: 2> => |H>\n"
            "        value |grid: 2: 3> => |e>\n"
            "        value |grid: 2: 4> => |l>\n"
            "        value |grid: 2: 5> => |l>\n"
            "        value |grid: 2: 6> => |o>\n\n"
            "        -- display the resulting grid:\n"
            "        display-grid[9, 5, value, \"*\"]\n"
            "            width:  9\n"
            "            height: 5\n"
            "\n"
            "            0      *   *   *   *   *   *   *   *   *\n"
            "            1      *   *   *   *   *   *   *   *   *\n"
            "            2      *   *   H   e   l   l   o   *   *\n"
            "            3      *   *   *   *   *   *   *   *   *\n"
            "            4      *   *   *   *   *   *   *   *   *\n\n"
            "    see also:\n"
            "        learn-grid";

    operator_usage_map.map["how-many"] =
            "\nhow-many:\n"
            "    description:\n"
            "        how-many sp\n"
            "        counts the number of kets in a superposition\n\n"
            "    examples:\n"
            "        how-many split |abcdef>\n"
            "            |number: 6>\n\n"
            "    see also:\n"
            "        measure-currency, show-many";

    operator_usage_map.map["show-many"] =
            "\nshow-many:\n"
            "    description:\n"
            "        show-many seq\n"
            "        counts the number of superpositions in a sequence\n\n"
            "    examples:\n"
            "        show-many ssplit |abcdef>\n"
            "            |number: 6>\n\n"
            "    see also:\n"
            "        how-many, measure-currency, how-many";

    operator_usage_map.map["measure-currency"] =
            "\nmeasure-currency:\n"
            "    description:\n"
            "        measure-currency sp\n"
            "        measures the \"currency\" used by a superposition\n"
            "        Ie, the sum of the coefficients of all the kets in the given superposition\n"
            "        If the superposition is \"clean\" then measure-currency is the same as the how-many operator\n\n"
            "    examples:\n"
            "        measure-currency (3|a> + 1.2|b> + 0.1|c>)\n"
            "            |number: 4.3>\n\n"
            "    see also:\n"
            "        how-many, show-many, clean";

    operator_usage_map.map["reverse"] =
            "\nreverse:\n"
            "    description:\n"
            "        reverse sp\n"
            "        reverse the given superposition\n\n"
            "    examples:\n"
            "        reverse (5.1|a> + 3.7|b> + |c> - 2.1|d>)\n"
            "            - 2.100000|d> + |c> + 3.700000|b> + 5.100000|a>\n\n"
            "    see also:\n"
            "        sreverse";

    operator_usage_map.map["sreverse"] =
            "\nsreverse:\n"
            "    description:\n"
            "        sreverse seq\n"
            "        reverse the given sequence\n\n"
            "    examples:\n"
            "        sreverse (5.1|a> . 3.7|b> . |c>)\n"
            "            |c> . 3.700000|b> . 5.100000|a>\n\n"
            "    see also:\n"
            "        reverse";

    operator_usage_map.map["sp2seq"] =
            "\nsp2seq:\n"
            "    description:\n"
            "        sp2seq sp\n"
            "        convert the given superposition into a sequence\n\n"
            "    examples:\n"
            "        sp2seq (|a> + |b> + |c>)\n"
            "            |a> . |b> . |c>\n\n"
            "    see also:\n"
            "        seq2sp";

    operator_usage_map.map["seq2sp"] =
            "\nseq2sp:\n"
            "    description:\n"
            "        seq2sp seq\n"
            "        convert the given sequence into a superposition\n\n"
            "    examples:\n"
            "        seq2sp (|a> . |b> . |c>)\n"
            "            |a> + |b> + |c>\n\n"
            "    see also:\n"
            "        sp2seq";

    operator_usage_map.map["plus"] =
            "\nplus:\n"
            "    description:\n"
            "        plus[n] ket\n"
            "        add n to the value in the ket, leaving the coefficient unchanged\n\n"
            "    examples:\n"
            "        plus[5] |3.1415>\n"
            "            |8.1415>\n\n"
            "    see also:\n"
            "        minus, times-by, divide-by, int-divide-by, mod, round";

    operator_usage_map.map["minus"] =
            "\nminus:\n"
            "    description:\n"
            "        minus[n] ket\n"
            "        subtract n from the value in the ket, leaving the coefficient unchanged\n\n"
            "    examples:\n"
            "        minus[2] |3.1415>\n"
            "            |1.1415>\n"
            "    see also:\n"
            "        plus, times-by, divide-by, int-divide-by, mod, round";

    operator_usage_map.map["times-by"] =
            "\ntimes-by:\n"
            "    description:\n"
            "        times-by[n] ket\n"
            "        times the value in the ket by n, leaving the coefficient unchanged\n\n"
            "    examples:\n"
            "        times-by[5] |6.1>\n"
            "            |30.5>\n\n"
            "    see also:\n"
            "        plus, minus, divide-by, int-divide-by, mod, round\n"
            "        temperature-conversion.sw3";

    operator_usage_map.map["divide-by"] =
            "\ndivide-by:\n"
            "    description:\n"
            "        divide-by[n] ket\n"
            "        divide the value in the ket by n, leaving the coefficient unchanged\n\n"
            "    examples:\n"
            "        divide-by[5] |625.5>\n"
            "            |125.1>\n\n"
            "    see also:\n"
            "        plus, minus, times-by, int-divide-by, mod, round";

    operator_usage_map.map["int-divide-by"] =
            "\nint-divide-by:\n"
            "    description:\n"
            "        int-divide-by[n] ket\n"
            "        integer divide the value in the ket by n, leaving the coefficient unchanged\n\n"
            "    examples:\n"
            "        int-divide-by[1000] |123456>\n"
            "            |123>\n\n"
            "    see also:\n"
            "        plus, minus, times-by, divide-by, mod, round";

    operator_usage_map.map["mod"] =
            "\nmod:\n"
            "    description:\n"
            "        mod[n] ket\n"
            "        apply mod n to the value in the ket by n, leaving the coefficient unchanged\n\n"
            "    examples:\n"
            "        mod[1000] |1234567>\n"
            "            |567>\n\n"
            "    see also:\n"
            "        plus, minus, times-by, divide-by, int-divide-by, round";

    operator_usage_map.map["round"] =
            "\nround:\n"
            "    description:\n"
            "        round[n] ket\n"
            "        round the value in the ket to n places, leaving the coefficient unchanged\n"
            "        If you need more decimal places in your kets, use the --places command line option.\n"
            "        The default is currently set to 5\n\n"
            "    examples:\n"
            "        round[3] |3.14159>\n"
            "            |3.142>\n\n"
            "    see also:\n"
            "        plus, minus, times-by, divide-by, int-divide-by, mod";

    operator_usage_map.map["to-upper"] =
            "\nto-upper:\n"
            "    description:\n"
            "        to-upper ket\n"
            "        set all characters to upper case\n\n"
            "        to-upper[i1, i2, ..., in] ket\n"
            "        change i'th characters to upper case\n\n"
            "    examples:\n"
            "        to-upper |fred>\n"
            "            |FRED>\n\n"
            "        to-upper[1] |fred>\n"
            "            |Fred>\n\n"
            "        to-upper[1,3,5] |abcdefg>\n"
            "            |AbCdEfg>\n\n"
            "    see also:\n"
            "        to-lower";

    operator_usage_map.map["to-lower"] =
            "\nto-lower:\n"
            "    description:\n"
            "        to-lower ket\n"
            "        set all characters to lower case\n\n"
            "        to-lower[i1, i2, ..., in] ket\n"
            "        change i'th characters to lower case\n\n"
            "    examples:\n"
            "        to-lower |FRED>\n"
            "            |fred>\n\n"
            "        to-lower[1] |FRED>\n"
            "            |fRED>\n\n"
            "        to-lower[1,3,5] |ABCDEFG>\n"
            "            |aBcDeFG>\n\n"
            "    see also:\n"
            "        to-upper";

    operator_usage_map.map["split"] =
            "\nsplit:\n"
            "    description:\n"
            "        split ket\n"
            "        splits the ket into a superposition\n\n"
            "        split[\"str\"] ket\n"
            "        splits the ket into a superposition, splitting on str\n\n"
            "    examples:\n"
            "        split |abcde>\n"
            "            |a> + |b> + |c> + |d> + |e>\n\n"
            "        split[\"d\"] |abcdef>\n"
            "            |abc> + |ef>\n\n"
            "        split[\"g\"] split[\"d\"] |abcdefghij>\n"
            "            |abc> + |ef> + |hij>\n\n"
            "    see also:\n"
            "        ssplit";

    operator_usage_map.map["ssplit"] =
            "\nssplit:\n"
            "    description:\n"
            "        ssplit ket\n"
            "        splits the ket into a sequence\n\n"
            "        ssplit[\"str\"] ket\n"
            "        splits the ket into a sequence, splitting on str\n\n"
            "    examples:\n"
            "        ssplit |abcde>\n"
            "            |a> . |b> . |c> . |d> . |e>\n\n"
            "        ssplit[\", \"] |a, b, c>\n"
            "            |a> . |b> . |c>\n\n"
            "        ssplit[\" and \"] |a, b, c and d>\n"
            "            |a, b, c> . |d>\n\n"
            "        ssplit[\", \"] ssplit[\" and \"] |a, b, c and d>\n"
            "            |a> . |b> . |c> . |d>\n\n"
            "    see also:\n"
            "        split, smerge";

    operator_usage_map.map["extract-category"] =
            "\nextract-category:\n"
            "    description:\n"
            "        extract-category ket\n"
            "        extract the \"category\" from the given ket\n"
            "        categories are separated by \": \"\n"
            "        with the most general category on the left, and the most specific on the right\n"
            "        for example |animal: mammal: dog>\n"
            "        has the most general category \"animal\", then the category \"mammal\" and then finally the \"value\" dog\n"
            "        categories can be considered a type for the object\n"
            "        Eg, |word: house> says house is a type of word\n"
            "        and |food: apple> says apple is a type of food\n"
            "        and we can define operators with respect to them\n"
            "        Eg, op |food: *> #=> ...\n"
            "        will define \"op\" with respect to all objects of type\\category \"food\".\n\n"
            "    examples:\n"
            "        -- if there is no category, then return the empty ket:\n"
            "        -- NB: this is in contrast to the python version of the Semantic DB which would instead return |dog>\n"
            "        extract-category |dog>\n"
            "            |>\n\n"
            "        -- remove the \"value\" from the ket:\n"
            "        -- in other words, extract the category of the ket\n"
            "        extract-category |animal: mammal: dog>\n"
            "            |animal: mammal>\n\n"
            "        -- remove the \"value\" from the ket, and then the most specific \"category\":\n"
            "        extract-category extract-category |animal: mammal: dog>\n"
            "            |animal>\n\n"
            "        -- or using the powered-operator notation:\n"
            "        extract-category^2 |animal: mammal: dog>\n"
            "            |animal>\n\n"
            "        -- an abstract example:\n"
            "        extract-category |a: b: c: d: e: f>\n"
            "            |a: b: c: d: e>\n\n"
            "    see also:\n"
            "        extract-value, extract-head, extract-tail";

    operator_usage_map.map["extract-value"] =
            "\nextract-value:\n"
            "    description:\n"
            "        extract-value ket\n"
            "        extract the value, ie, remove the category, from the given ket\n"
            "        categories are separated by \": \"\n"
            "        with the most general category on the left, and the most specific on the right\n"
            "        for example |animal: mammal: dog>\n"
            "        has the most general category \"animal\", then the category \"mammal\" and then finally the \"value\" dog\n"
            "        categories can be considered a type for the object\n"
            "        and values are specific examples of that type\n"
            "        Eg, |food: apple> says apple is a type of food, and the value of |food: apple> is apple\n\n"
            "    examples:\n"
            "        -- if there is no category, then return unchanged:\n"
            "        extract-value |dog>\n"
            "            |dog>\n\n"
            "        extract-value |animal: mammal: dog>\n"
            "            |dog>\n\n"
            "        -- an abstract example:\n"
            "        extract-value |a: b: c: d: e: f>\n"
            "            |f>\n\n"
            "    see also:\n"
            "        extract-category, extract-head, extract-tail";

    operator_usage_map.map["extract-head"] =
            "\nextract-head:\n"
            "    description:\n"
            "        extract-head ket\n"
            "        categories are separated by \": \"\n"
            "        with the most general category on the left, and the most specific on the right\n"
            "        for example |animal: mammal: dog>\n"
            "        has the most general category \"animal\", then the category \"mammal\" and then finally the \"value\" dog\n"
            "        This list of categories and the value can be considered a type of list\n"
            "        extract-head returns the first element, or head, of this list\n\n"
            "    examples:\n"
            "        -- if there is no category, then return unchanged:\n"
            "        extract-head |dog>\n"
            "            |dog>\n\n"
            "        extract-head |animal: mammal: dog>\n"
            "            |animal>\n\n"
            "        -- an abstract example:\n"
            "        extract-head |a: b: c: d: e: f>\n"
            "            |a>\n\n"
            "    see also:\n"
            "        extract-category, extract-value, extract-tail";

    operator_usage_map.map["extract-tail"] =
            "\nextract-tail:\n"
            "    description:\n"
            "        extract-tail ket\n"
            "        categories are separated by \": \"\n"
            "        with the most general category on the left, and the most specific on the right\n"
            "        for example |animal: mammal: dog>\n"
            "        has the most general category \"animal\", then the category \"mammal\" and then finally the \"value\" dog\n"
            "        This list of categories and the value can be considered a type of list\n"
            "        extract-tail returns the tail of this list\n"
            "        Ie, with the first category removed\n\n"
            "    examples:\n"
            "        -- if there is no category, then return the empty ket:\n"
            "        extract-tail |dog>\n"
            "            |>\n\n"
            "        extract-tail |animal: mammal: dog>\n"
            "            |mammal: dog>\n\n"
            "        -- an abstract example:\n"
            "        extract-tail |a: b: c: d: e: f>\n"
            "            |b: c: d: e: f>\n\n"
            "    see also:\n"
            "        extract-category, extract-value, extract-head";

    operator_usage_map.map["print"] =
            "\nprint:\n"
            "    description:\n"
            "        print ket\n"
            "        print the given ket to standard out, appending a new line\n"
            "        often used with the infix operators _ and __ which join ket labels, where __ inserts an extra space\n"
            "        also frequently used with the smerge[] operator\n"
            "        print returns the input ket, so it can be chained with other operators\n\n"
            "    examples:\n"
            "        print |Just a short sentence.>\n"
            "            Just a short sentence.\n"
            "            |Just a short sentence.>\n"
            "        print (|A> __ |short> __ |example> _ |.>)\n"
            "            A short example.\n"
            "            |A short example.>\n\n"
            "        print smerge[\", \"] (|a> . |b> . |c>)\n"
            "            a, b, c\n"
            "            |a, b, c>\n\n"
            "    see also:\n"
            "        to-upper, to-lower, smerge";

    operator_usage_map.map["threshold-filter"] =
            "\nthreshold-filter:\n"
            "    description:\n"
            "        threshold-filter[t] ket\n"
            "        if x < t, return 0, else return x\n"
            "        combined with drop, eg: drop threshold-filter[t] sp\n"
            "        filter the given superposition to only those with coefficients >= t.\n\n"
            "    examples:\n"
            "        threshold-filter[2] (3|a> + 2.2|b> - 3 |c> + |d>)\n"
            "            3|a> + 2.200000|b> + 0|c> + 0|d>\n\n"
            "        drop threshold-filter[2] (3|a> + 2.2|b> - 3 |c> + |d>)\n"
            "            3|a> + 2.200000|b>\n\n"
            "    see also:\n"
            "        not-threshold-filter";

    operator_usage_map.map["not-threshold-filter"] =
            "\nnot-threshold-filter:\n"
            "    description:\n"
            "        not-threshold-filter[t] ket\n"
            "        if x <= t, return x, else return 0\n\n"
            "    examples:\n"
            "        not-threshold-filter[2] (3|a> + 2.2|b> - 3 |c> + |d>)\n"
            "            0|a> + 0|b> - 3|c> + |d>\n\n"
            "    see also:\n"
            "        threshold-filter";

    operator_usage_map.map["sigmoid-in-range"] =
            "\nsigmoid-in-range:\n"
            "    description:\n"
            "        sigmoid-in-range[a, b] ket\n"
            "        if a <= x <= b, return x, else return 0\n\n"
            "    examples:\n"
            "        sigmoid-in-range[2,4] (|a> + 2|b> + 3|c> + 4|d> + 5|e>)\n"
            "            0|a> + 2|b> + 3|c> + 4|d> + 0|e>\n\n"
            "    see also:\n"
            "        threshold-filter";

}

std::string OperatorUsageMap::get_usage(const std::string &s) const {
    auto it = map.find(s);
    if (it == map.end()) { return ""; }
    return it->second;
}

bool OperatorUsageMap::usage_is_defined(const std::string &s) const {
    auto it = map.find(s);
    return it != map.end();
}