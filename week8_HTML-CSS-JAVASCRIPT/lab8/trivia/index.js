document.addEventListener("DOMContentLoaded", function() {
    let correct = document.querySelector(".correct");
    correct.addEventListener("click", function () {
        correct.style.backgroundColor = "green";
        document.querySelector("#feedback1").innerHTML = "Correct!";
    });

    let incorrects = document.querySelectorAll(".incorrect");
    for (let i = 0; i < incorrects.length; i++) {
        incorrects[i].addEventListener("click", function () {
            incorrects[i].style.backgroundColor = "red";
            document.querySelector("#feedback1").innerHTML = "Incorrect";
        });
    }
})