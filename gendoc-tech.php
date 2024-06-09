#!/usr/bin/php

<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="style.css">
        <title>test</title>
    </head>
    <style>
    body{
        font-family: sans-serif;
        background-color: #332B31;
        color: white;
    }
    h1{
        text-align: center;
        font-size: 50px;
        color: #B33E9B;
    }
    div{
        display: flex;
        flex-direction: row;
        flex-wrap: wrap;
        justify-content: space-around;
    }
    div>article{
        background-color: #B33E9B;
    }

    article{
        background-color: #804674;
        border-radius: 15px;
        padding: 1em;
        margin: 20px;
    }
    header>p{
        text-align: center;
    }
    footer{
        display: flex;
        justify-content: space-around;
        color: #804674;
        border-radius: 15px;
        padding: 1em;
        margin: 20px;
        flex-direction: row;
        flex-wrap: wrap;
    }
    </style>
<?php
    $line = file("fic_c");
    foreach($line as $key => $test){
        if ($key != 0) {
            $test=trim($test);
            $testH1=str_replace("src/","",$test,);
            $lines = file("$testH1");

    
?>
    <body>
        <header>
            <h1 class="test" ><?php echo $testH1 ?></h1>
    <?php
        $open_found = false;
        $total="";
        foreach ($lines as $key => $value){
            if( $key==0 && $open_found==false && preg_match('/\/\*\*/',$value)==true){
                $open_found = true;
            }
            else if(($open_found == true) && preg_match('/\*\//',$value)==true){
                $open_found = false ;
            }
            else if(($open_found == true) && preg_match('/\*\//',$value)==false){
                $total = $total . trim($value);
                for($i = 0; $i < strlen($total); $i++){
                    if($total[$i]=="*"){
                        $total[$i]= ' ';
                    }
                }
            }
        }
    ?>
                <p> <?php echo $total ?> </p>
        </header>
        <main>
            <article>
                <h2>DEFINE</h2>
    <?php
        $total=[];
        foreach ($lines as $key => $value){
            if(preg_match('/#define/',$value) || preg_match('/const/',$value)==true ){
                $suppr = array("#define","const","/**","*/",";","tabEntiers");
                $value=str_replace($suppr,"",$value);
                $total[$key] = trim($value) ;
            }
        }
    ?>
    <?php 
        foreach($total as $ligne){
    ?>
                <p><?php echo $ligne ?></p>
    <?php 
        }
    ?>
            </article>
            <article>
                <h2>STRUCTURE</h2>
                <div>
    <?php 
        $open_found = false;
        $total= [];
        foreach ($lines as $key => $value){
            if($open_found==false && preg_match('/typedef struct {/',$value)==true){
                $open_found = true;
            }
            else if ($open_found==true && preg_match('/}/',$value)==true){
                $total[$key]= $value ; 
                $open_found = false;
            }
            else if ($open_found==true && preg_match('/}/',$value)==false){
                $total[$key] = $value;
            }
        }
        $h3=[];
        $other=[];
        $compteur =0;
        $compteur_other = 0;
        $suppr=array("}","/**","*/","char","int","float","{");
        foreach($total as $ligne){
            if(preg_match('/}/',$ligne)==true){
                $h3[$compteur]=$ligne ;
                $h3[$compteur]=str_replace($suppr,"",$h3[$compteur]);
                $h3[$compteur]=str_replace(";",":",$h3[$compteur]);
                $compteur =$compteur+1;
            }else{
                $other[$compteur_other]=$compteur . $ligne;
                $compteur_other=$compteur_other+1;
            }
        }

        for($i = 0; $i < count($h3); $i++){
    ?>
                    <article>
                        <h3><?php echo trim($h3[$i]) ?></h3>
                        <pre>

    <?php 
        foreach($other as $ligne){
            if($i==$ligne[0]){
                $ligne[0]=" ";
                $ligne = str_replace($suppr,"",$ligne);
                $ligne=str_replace(";",":",$ligne);
                echo $ligne ;
            }
        }
    ?>
                        </pre>
                        
                    </article>          
    <?php
        }
    ?>
                </div>
            </article>
            <article>
                <h2>GLOBAL</h2>
    <?php
                foreach ($lines as $key => $value){
                    if(preg_match('/for/',$value)==false && (preg_match('/int/',$value)==true || preg_match('/char/',$value)==true || preg_match('/float/',$value)==true) && preg_match('/=/',$value)==true ){
                        $value=str_replace($suppr,"",$value);
                        $value=str_replace(";",":",$value);
                    ?>
                    <p> <?php echo trim($value) ?> </p>
                    <?php
                    }
                }
    ?>
            </article>
            <article>
                <h2>FONCTION ET PROCEDURE</h2>
    <?php
        $h3 = [];
        $brief =[];
        $return=[];
        $compteur = 0 ;
        $compteurbrief = 0 ;
        $compteurreturn = 0 ;
        foreach($lines as $value){
            if((preg_match('/int/',$value)==true || ( preg_match('/struct/',$value)==true && preg_match('/typedef/',$value)==false && preg_match('/\(/',$value)==true) || preg_match('/float/',$value)==true || preg_match('/bool/',$value)==true || preg_match('/void/',$value)==true) && preg_match('/{/',$value)==true && preg_match('/for/',$value)==false){
                $value=str_replace($suppr,"",$value);
                $start = 0 ;
                $h3[$compteur]=$value;
                $compteur=$compteur+1;
            }
        }  

        $compteurparam=0;
        $suppr=array("*","\\","brief","*","param","return");
        foreach($lines as $value){
            if (preg_match('/\\\brief/',$value)==true) {
                $value=str_replace($suppr,"",$value);
                $brief[$compteurbrief]=$value;
                $compteurbrief = $compteurbrief +1 ;
            }

            if (preg_match('/\\\param/',$value)==true){
                $value=str_replace($suppr,"",$value);
                $param[$compteurparam]=$compteurbrief . $value;
                $compteurparam=$compteurparam+1;
            }
            
            if (preg_match('/\\\return/',$value)==true) {
                $value=str_replace($suppr,"",$value);
                $return[$compteurreturn]=$compteurbrief . $value;
                $compteurreturn = $compteurreturn +1 ;
            }

        }

    ?>
                <div>
    <?php
        for($i = 0; $i < count($h3); $i++){
            $compteur=0;
    ?>
                    <article>
                        <h3><?php echo trim($h3[$i])?></h3>
                        <p><?php echo trim($brief[$i])?></p>
                        <h4>Parametres</h4>
                        <ul>
                            <?php
                                foreach($param as $valeur){
                                    if ($valeur[0]==$i+1) {
                                        $compteur = $compteur + 1;
                                        $valeur[0]=" ";
                            ?>    
                                <li> <?php echo trim($valeur) ?> </li>
                            <?php
                                    }
                                }
                                if($compteur==0){
                            ?>    
                                <li><?php echo "AUCUN" ?></li>
                            <?php
                                }
                            ?>
                        </ul>
                        <p>
                        <?php 
                        foreach($return as $valeur){
                            if ($valeur[0]==$i+1) {
                                $valeur[0]=" ";
                                echo trim("Retourne" . $valeur);
                            }
                        }
                        ?>
                        </p>
                    </article>
    <?php
        }
    ?>
                </div>
            </article>
        </main>
    </body>
    <?php
    }
}
?>
</html>
