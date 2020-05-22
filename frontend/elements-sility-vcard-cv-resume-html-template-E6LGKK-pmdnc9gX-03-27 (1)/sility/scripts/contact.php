<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	if(!empty($_POST['x']) && !empty($_POST['alfa']) && !empty($_POST['beta']) && !empty($_POST['delta']) && !empty($_POST['gamma']) && !empty($_POST['process']) && !empty($_POST['nuc']) && !empty($_POST['c'])) {
		$x = $_POST['x'];
		$alfa = $_POST['alfa'];
		$beta = $_POST['beta'];
		$delta = $_POST['delta'];
		$gamma = $_POST['gamma'];
		$process = $_POST['process'];
		$nuc = $_POST['nuc'];
		$c = $_POST['c'];
		$output = shell_exec("cd ../../../../api; ./pro $x $alfa $beta $delta $gamma $process $nuc $c");
		header( 'Location: ../simulation.html' ) ;
		//echo "<h4>$output</h4>";
	}else {
		echo "<h4>FALTO UN DATO</h4>";
	}
}
?>