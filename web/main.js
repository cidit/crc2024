const clifimage = document.getElementById("clif-image-dropdown")
let isopencliff = false
clifimage.onclick=(event) => {
    event.stopPropagation()
    isopencliff = !isopencliff
    const clifdropdown= document.getElementById("clif-dropdown")

    clifdropdown.style.display=isopencliff?"block":"none"
}

const princesseDropdown = document.getElementById("princesse-dropdown")
let isopenprincesse = false
princesseDropdown.onclick=() => {
    isopenprincesse = !isopenprincesse
    const Dropdown= document.getElementById("dropdown")

    Dropdown.style.display=isopenprincesse?"block":"none"
}