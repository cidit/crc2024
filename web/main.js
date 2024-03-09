const clifimage = document.getElementById("clif-image-dropdown")
let isopencliff = false
clifimage.onclick=(event) => {
    event.stopPropagation()
    isopencliff = !isopencliff
    const clifdropdown= document.getElementById("clif-dropdown")

    clifdropdown.style.display=isopencliff?"block":"none"
}

const Alexisimage = document.getElementById("Alexis-image-dropdown")
let isopenAlexis = false
Alexisimage.onclick=(event) => {
    event.stopPropagation()
    isopenAlexis = !isopenAlexis
    const Alexisdropdown= document.getElementById("Alexis-dropdown")

    Alexisdropdown.style.display=isopenAlexis?"block":"none"
}

const Féliximage = document.getElementById("Félix-image-dropdown")
let isopenFélix = false
Féliximage.onclick=(event) => {
    event.stopPropagation()
    isopenFélix = !isopenFélix
    const Félixdropdown= document.getElementById("Félix-dropdown")

    Félixdropdown.style.display=isopenFélix?"block":"none"
}

const Guillaumeimage = document.getElementById("Guillaume-image-dropdown")
let isopenGuillaume = false
Guillaumeimage.onclick=(event) => {
    event.stopPropagation()Guillaume
    isopenGuillaume = !isopenGuillaume
    const Guillaumedropdown= document.getElementById("Guillaume-dropdown")

    Guillaumedropdown.style.display=isopenGuillaume?"block":"none"
}

// const princesseDropdown = document.getElementById("princesse-dropdown")
// let isopenprincesse = false
// princesseDropdown.onclick=() => {
//     isopenprincesse = !isopenprincesse
//     const Dropdown= document.getElementById("dropdown")

//     Dropdown.style.display=isopenprincesse?"block":"none"
// }

// const ### = document.getElementById("###")
// let isopen# = false
// princesseDropdown.onclick=() => {
//     isopen# = !isopen#
//     const Dropdown= document.getElementById("dropdown")

//     Dropdown.style.display=isopenprincesse?"block":"none"
// }