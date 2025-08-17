document.getElementById("btn").addEventListener("click", async () => {
    const res = await fetch("/save-name", {
        method: "POST",
        headers: {
            "Content-Type": "text/json"
        },
        body: JSON.stringify({ "name": "Nicolas Okuly" })
    });
    console.log(res.status)
})