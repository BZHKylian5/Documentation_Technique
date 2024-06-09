<?php

// Charger le fichier HTML
$html = file_get_contents("index.html");

// Créer un conteneur Docker
$container = new Docker\Container("sae103-html2pdf");

// Lancer la conversion
$container->exec("wkhtmltopdf index.html index.pdf");

// Attendre la fin de la conversion
$container->wait();

// Récupérer le fichier PDF
$pdf = $container->get("index.pdf");

// Enregistrer le fichier PDF
file_put_contents("index.pdf", $pdf);

?>

