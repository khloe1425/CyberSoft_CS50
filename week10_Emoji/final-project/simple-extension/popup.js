document.addEventListener('DOMContentLoaded', () => {
    document.getElementById('changeColor').addEventListener('click', changeBackgroundColor);
});

function changeBackgroundColor() {
    chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
        chrome.tabs.executeScript(
            tabs[0].id,
            { code: 'document.body.style.backgroundColor = "red";' }
        );
    });
}
