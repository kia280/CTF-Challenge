document.querySelector("#list").addEventListener("submit", (e) => {
    let input = document.querySelector("#input").value.split('\n');
    let rootNode = document.createElement("UCCU");
    for (let line of input) {
        let queryItem = document.createElement("query");
        let queryText = document.createTextNode(line);
        queryItem.appendChild(queryText);
        rootNode.appendChild(queryItem);
    }
    let xmlSerializer = new XMLSerializer();
    let xmlString = xmlSerializer.serializeToString(rootNode);
    fetch("/api/query.php", {
        method: 'POST',
        body: xmlString,
    })
    .then(response => response.json())
    .then(data => {
        let tableNode = document.querySelector("#result");
        let idx = 1;
        document.querySelector("#result-section").classList.remove("d-none");
        document.querySelector("#div-res").classList.remove("d-none");
        tableNode.innerHTML = "";
        for (let item of data.queryResult) {
            let tr = document.createElement("tr");
            let th = document.createElement("th");
            let tquery = document.createElement("td");
            let tvalue = document.createElement("td");
            th.appendChild(document.createTextNode(idx++));
            tquery.appendChild(document.createTextNode(item.query));
            tvalue.appendChild(document.createTextNode(item.value));
            tr.appendChild(th);
            tr.appendChild(tquery);
            tr.appendChild(tvalue);
            tableNode.appendChild(tr);
        }
        $('html, body').animate({
            scrollTop: $("#result-section").offset().top
        }, 500);
    });
    e.preventDefault();
});


particlesJS.load('particles-js', 'assets/particles.json', function () {
    console.log('callback - particles.js config loaded');
});
