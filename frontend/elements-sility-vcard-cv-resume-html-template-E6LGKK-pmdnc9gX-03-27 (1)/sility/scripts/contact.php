<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
	if(!empty($_POST['x']) && !empty($_POST['alfa']) && !empty($_POST['beta']) && !empty($_POST['delta']) && !empty($_POST['gamma']) && !empty($_POST['process']) && !empty($_POST['nuc']) && !empty($_POST['c'])) {
		exec('./pro.exe', $out);
	}
}
?>