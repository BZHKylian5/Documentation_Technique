#!/usr/bin/php
<?php
// Inclure la bibliothèque Dompdf
require_once 'vendor/autoload.php';

// Créer une instance de Dompdf
use Dompdf\Dompdf;
$dompdf = new Dompdf();

// Chemin du fichier HTML à convertir
$htmlFile = 'chemin/vers/votre/fichier.html';

// Lire le contenu HTML depuis le fichier
$html = file_get_contents($htmlFile);

// Charger le contenu HTML dans Dompdf
$dompdf->loadHtml($html);

// (Optionnel) Vous pouvez définir des options de format et d'orientation du PDF
$dompdf->setPaper('A4', 'portrait');

// Rendre le PDF
$dompdf->render();

// Enregistrer le PDF généré dans un fichier
$outputFile = 'chemin/vers/votre/fichier.pdf';
file_put_contents($outputFile, $dompdf->output());

echo 'Fichier PDF généré avec succès.';
?>

