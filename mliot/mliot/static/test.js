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

function getImage(image_no)
{
  var ims = [
    "DrewFace.png",
    "happy1.png",
    "meh1.png",
    "mad1.png"];

    return "../statics/images/" + ims[image_no % ims.length]
}
