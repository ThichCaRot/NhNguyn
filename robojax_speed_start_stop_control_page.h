const char speed_control_page_part1[]  PROGMEM = R"robojaxSpeed1(
<!DOCTYPE html>
<html>
<head>
<title>Team 7</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
* {box-sizing: border-box}

.container {
  width: 100%;
  background-color: #ddd;
}

.skills {
  text-align: right;
  padding-top: 10px;
  padding-bottom: 10px;
  color: white;
}

.html {width: )robojaxSpeed1";




const char speed_control_page_part2[] PROGMEM = R"robojaxSpeed2(%; 
background-color: #f44336;}
.nextprev a.rj-right, .nextprev a.rj-left {
    background-color: #f44336;
    color: #ffffff;
    border-color: #f44336;
}
.nextprev a {
    font-size: 22px;
    border: 1px solid #cccccc;
}
.rj-right {
    float: right!important;
}
.rj-btn, .rj-button {
    border: none;
    display: inline-block;
    padding: 8px 16px;
    vertical-align: middle;
    overflow: hidden;
    text-decoration: none;
    color: inherit;
    background-color: inherit;
    text-align: center;
    cursor: pointer;
    white-space: nowrap;
}
</style>
<meta charset="UTF-8">
</head>
<body>

<h1>Team Báo số 7</h1>
<div class="container">
<div class="skills html">)robojaxSpeed2";



const char speed_control_page_part3[] PROGMEM = R"robojaxSpeed3(%</div> 
</div>
<hr>
<div class="nextprev">
<a class="rj-left rj-btn" href="/speed?do=slower">< Slower</a>
<a class="rj-right rj-btn" href="/speed?do=faster">Faster ></a>
</div>

<hr>
<h2>Start of Stop</h2>
<div class="nextprev">
<a class="rj-left rj-btn" href="/stop?do=START">START</a>
<a class="rj-right rj-btn" href="/stop?do=STOP">STOP</a>
</div>
</body>
</html>)robojaxSpeed3";
