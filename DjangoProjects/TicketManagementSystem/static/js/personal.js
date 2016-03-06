function openunfinished()
{var divD = document.getElementById("unfinish");divD.style.display = "block";
var divD = document.getElementById("finish");divD.style.display = "none";var divD = document.getElementById("information");
divD.style.display = "none";}
function openfinished()
{var divD = document.getElementById("finish");divD.style.display = "block";
var divD = document.getElementById("information");divD.style.display = "none";
var divD = document.getElementById("unfinish");divD.style.display = "none";}
function openinformation()
{var divD = document.getElementById("information");divD.style.display = "block";
var divD = document.getElementById("unfinish");divD.style.display = "none";
var divD = document.getElementById("finish");divD.style.display = "none";}
function clickback(num)
{
	var buttondiv = document.getElementById("button"+num);
	var backinputdivone = document.getElementById("backinput"+num+"one");
	var backinputdivtwo = document.getElementById("backinput"+num+"two");
	var backbuttondiv = document.getElementById("backbutton"+num);
	if(buttondiv.innerHTML=="编辑")
	{
		buttondiv.innerHTML="收起";
		backinputdivone.style.display="block";
		backinputdivtwo.style.display="block";
		backbuttondiv.style.display="block";
		var backdiv = document.getElementById("backdiv"+num);
            backdiv.style.height = "150px";
	    var number=new Array();
	    number[0]="one";
	    number[1]="two";
	    number[2]="three";
	    number[3]="four";
	
	    for (var i=0;i<number.length;i++)
	    {
		    if(number[i]!=num)
		    {
			    backdiv = document.getElementById("backdiv"+number[i]);
			    backdiv.style.height = "0px";
				backinputdivone = document.getElementById("backinput"+number[i]+"one");
				backinputdivtwo = document.getElementById("backinput"+number[i]+"two");
				backbuttondiv = document.getElementById("backbutton"+number[i]);
				backinputdivone.style.display="none";
		        backinputdivtwo.style.display="none";
		        backbuttondiv.style.display="none";
				buttondiv = document.getElementById("button"+number[i]);
				buttondiv.innerHTML="编辑";
		    }
	    }
	}
	else
	{
		buttondiv.innerHTML="编辑";
		backinputdivone.style.display="none";
		backinputdivtwo.style.display="none";
		backbuttondiv.style.display="none";
		var backdiv = document.getElementById("backdiv"+num);
            backdiv.style.height = "0px";
	}
}