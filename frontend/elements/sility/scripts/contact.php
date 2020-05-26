<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	if(!empty($_POST['tiempo']) && !empty($_POST['x']) && !empty($_POST['alfa']) && !empty($_POST['beta']) && !empty($_POST['delta']) && !empty($_POST['gamma']) && !empty($_POST['process']) && !empty($_POST['nuc']) && !empty($_POST['c'])) {
		$tiempo = $_POST['tiempo'];
		$x = $_POST['x'];
		$alfa = $_POST['alfa'];
		$beta = $_POST['beta'];
		$delta = $_POST['delta'];
		$gamma = $_POST['gamma'];
		$process = $_POST['process'];
		$nuc = $_POST['nuc'];
		$c = $_POST['c'];
		shell_exec("cd ../../../../api; g++ project.cpp -o pro");
		$output = shell_exec("cd ../../../../api; ./pro $x $alfa $beta $delta $gamma $process $nuc $c $tiempo");

		// // $csvFile = file('prueba.txt');
		// $CSVfp = fopen("prueba.txt", "r");
		// if($CSVfp !== FALSE) {
		//  while(! feof($CSVfp)) {
		// 	$data[] = fgetcsv($CSVfp);
		// 	print_r($data);
		// 	echo "<br>";
		//  }
		// }
		// fclose($CSVfp);

		// // header('Content-Type: text/plain');
		// $js_array = json_encode($data);
		
		header( 'Location: ../simulPlay.html' ) ;
		// echo "<h4>$output</h4>" ;
	}else {
		echo "<h4>FALTO UN DATO</h4>";
	}
}
?>
<button type="submit" class="button solid-button2 purple" onClick="history.back();return true;">Regresar</button>
	
