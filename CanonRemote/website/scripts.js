function setExposureTime() {
	var field = document.getElementById("exposuretime");
	var expTime = field.value;

	var request = new XMLHttpRequest();
	var data = 0;
	request.open("GET", "exposuretime.php?value=" + expTime, true);     
	request.send(null);
	request.onreadystatechange = function () {
		if (request.readyState == 4 && request.status == 200) {
			data = request.responseText;
			field.value = data;
		} else if (request.readyState == 4 && request.status == 500) {
			alert ("server error");
			return ("fail");
		} else if (request.readyState == 4 && request.status != 200 && request.status != 500 ) {
			alert ("Something went wrong!");
			return ("fail");
		}
	}
	return 0;
}

function changeImageLoop() {
	var button = document.getElementById("loopon");

	var request = new XMLHttpRequest();
	var data = 0;
	request.open("GET", "imageloop.php?value=dummy", true);     
	request.send(null);
	request.onreadystatechange = function () {
		if (request.readyState == 4 && request.status == 200) {
			data = request.responseText;
			if (!(data.localeCompare("0"))) {
				button.src = "data/button_green.png";
				window.location.reload(true);
			} else if (!(data.localeCompare("1"))) {
				button.src = "data/button_red.png";
				window.location.reload(true);
			} else if (!(data.localeCompare("fail"))) {
				alert ("Something went wrong!");
				return ("fail");
			} else {
				alert ("Something went wrong!");
				return ("fail"); 
			}
		} else if (request.readyState == 4 && request.status == 500) {
			alert ("server error");
			return ("fail");
		} else if (request.readyState == 4 && request.status != 200 && request.status != 500 ) {
			alert ("Something went wrong!");
			return ("fail");
		}
	}
	return 0;
}

function changeFocus() {
	var button = document.getElementById("focuson");

	var request = new XMLHttpRequest();
	var data = 0;
	request.open("GET", "focus.php?value=dummy", true);     
	request.send(null);
	request.onreadystatechange = function () {
		if (request.readyState == 4 && request.status == 200) {
			data = request.responseText;
			if (!(data.localeCompare("0"))) {
				button.src = "data/button_green.png";
				window.location.reload(true);
			} else if (!(data.localeCompare("1"))) {
				button.src = "data/button_red.png";
				window.location.reload(true);
			} else if (!(data.localeCompare("fail"))) {
				alert ("Something went wrong!");
				return ("fail");
			} else {
				alert ("Something went wrong!");
				return ("fail"); 
			}
		} else if (request.readyState == 4 && request.status == 500) {
			alert ("server error");
			return ("fail");
		} else if (request.readyState == 4 && request.status != 200 && request.status != 500 ) {
			alert ("Something went wrong!");
			return ("fail");
		}
	}
	return 0;
}

function changeTrigger() {
	var button = document.getElementById("triggeron");

	var request = new XMLHttpRequest();
	var data = 0;
	request.open("GET", "trigger.php?value=dummy", true);     
	request.send(null);
	request.onreadystatechange = function () {
		if (request.readyState == 4 && request.status == 200) {
			data = request.responseText;
			if (!(data.localeCompare("0"))) {
				button.src = "data/button_green.png";
				window.location.reload(true);
			} else if (!(data.localeCompare("1"))) {
				button.src = "data/button_red.png";
				window.location.reload(true);
			} else if (!(data.localeCompare("fail"))) {
				alert ("Something went wrong!");
				return ("fail");
			} else {
				alert ("Something went wrong!");
				return ("fail"); 
			}
		} else if (request.readyState == 4 && request.status == 500) {
			alert ("server error");
			return ("fail");
		} else if (request.readyState == 4 && request.status != 200 && request.status != 500 ) {
			alert ("Something went wrong!");
			return ("fail");
		}
	}
	return 0;
}
