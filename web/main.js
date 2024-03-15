const princesseDropdown2 = document.getElementById("princesse-dropdown2")
let isopenprincesse2 = false
princesseDropdown2.onclick = () => {
    isopenprincesse2 = !isopenprincesse2
    const Dropdown2 = document.getElementById("dropdown2")

    Dropdown2.style.display = isopenprincesse2 ? "block" : "none"
}


const cliffimage2 = document.getElementById("cliff-image-dropdown2")
let isopencliff2 = false
cliffimage2.onclick = (event) => {
    event.stopPropagation()
    isopencliff2 = !isopencliff2
    const cliffdropdown2 = document.getElementById("cliff-dropdown2")

    cliffdropdown2.style.display = isopencliff2 ? "block" : "none"
}

const Youssefbuttonqualité2 = document.getElementById("Youssef-qualité2")
let isopenYoussefQualité2 = false
Youssefbuttonqualité2.onclick = (event) => {
    event.stopPropagation()
    isopenYoussefQualité2 = !isopenYoussefQualité2
    const Youssefdropdownqualité2 = document.getElementById("Youssef-dropdown-qualité2")

    Youssefdropdownqualité2.style.display = isopenYoussefQualité2 ? "block" : "none"
}
const Youssefbuttondefault2 = document.getElementById("Youssef-défault2")
let isopenYoussefdefault2 = false
Youssefbuttondefault2.onclick = (event) => {
    event.stopPropagation()
    isopenYoussefdefault2 = !isopenYoussefdefault2
    const Youssefdropdowndefault2 = document.getElementById("Youssef-dropdown-défault2")

    Youssefdropdowndefault2.style.display = isopenYoussefdefault2 ? "block" : "none"
}





const princesseDropdown = document.getElementById("princesse-dropdown")
const princesseDropdown1 = document.getElementById("dropdown")
let isopenprincesse = false
princesseDropdown1 = princesseDropdown.onclick = () => {
    isopenprincesse = !isopenprincesse
    const Dropdown = document.getElementById("dropdown")

    Dropdown.style.display = isopenprincesse ? "block" : "none"
}



const boxDropdown = document.getElementById("box-dropdown")
// const boxDropdown1 = document.getElementById("dropdownBox")
let isopenbox = false
boxDropdown1 = boxDropdown.onclick = () => {
    isopenbox = !isopenbox
    const Dropdown = document.getElementById("dropdownBox")

    Dropdown.style.display = isopenbox ? "block" : "none"
}

const buttonDropdown = document.getElementById("btn-dropdown")
// const buttonDropdown1 = document.getElementById("dropdown")
let isopenbutton = false
buttonDropdown = buttonDropdown.onclick = (event) => {
    event.stopPropagation()
    isopenbutton = !isopenbutton
    const buttonDropdown = document.getElementById("dropdownbtn")

    buttonDropdown.style.display = isopenbutton ? "block" : "none"
}

// const Youssefimage = document.getElementById("Youssef-image-dropdown")
// let isopenYoussef = false
// Youssefimage.onclick=(event) => {
//     event.stopPropagation()
//     isopenYoussef = !isopenYoussef
//     const Youssefdropdown= document.getElementById("Youssef-dropdown")

//     Youssefdropdown.style.display=isopenYoussef?"block":"none"
// }



// const ### = document.getElementById("###")
// let isopen# = false
// princesseDropdown.onclick=() => {
//     isopen# = !isopen#
//     const Dropdown= document.getElementById("dropdown")

//     Dropdown.style.display=isopenprincesse?"block":"none"
// }





// const princesseDropdown = document.getElementById("princesse-dropdown")
// const princesseDropdown1 = document.getElementById("dropdown")
// let isopenprincesse = false
// princesseDropdown1 = princesseDropdown.onclick = () => {
//     isopenprincesse = !isopenprincesse
//     const Dropdown = document.getElementById("dropdown")

//     Dropdown.style.display = isopenprincesse ? "block" : "none"
// }

// const Youssefimage = document.getElementById("Youssef-image-dropdown")
// let isopenYoussef = false
// Youssefimage.onclick=(event) => {
//     event.stopPropagation()
//     isopenYoussef = !isopenYoussef
//     const Youssefdropdown= document.getElementById("Youssef-dropdown")

//     Youssefdropdown.style.display=isopenYoussef?"block":"none"
// }