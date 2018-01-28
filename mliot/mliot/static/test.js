function OnClick()
{
  confirm("Button Pressed.");
  //document.getElementById('myText').innerHTML = "JS Works!"
}

function getCharId()
{
  confirm("Press a button.")
  var PetId = prompt("Please enter your μPet's ID");
  if (PetId != null)
  {
    document.getElementById('Test').innerHTML = PetId;
  }
}
