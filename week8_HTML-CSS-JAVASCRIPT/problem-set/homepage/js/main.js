// Add active class to the current nav link 
let header = document.getElementById('navbarNav'); 
let navLink = header.getElementsByClassName('nav-link'); 
// console.log(navItem);
for (let i = 0; i < navLink.length; i++) {
    navItem[i].addEventListener('click', function() {
        let current = document.getElementsByClassName('active'); 
        current[0].className = current[0].className.replace(" active", ""); 
        this.className += " active";
        console.log(this)
    })
}
