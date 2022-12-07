Module.addOnPostRun(() => {
  //generate vector for consumption type names
  const vector = new Module.StringVector();
  const strings = [
    "Commercial Coal",
    "Commercial Distillate Fuel Oil",
    "Commercial Geothermal",
    "Commercial Hydropower",
    "Commercial Kerosene",
    "Commercial Petroleum",
    "Commercial Natural Gas",
    "Commercial Solar",
    "Commercial Wind",
    "Commercial Wood",
    "Electric Power Coal",
    "Electric Power Distillate Fuel Oil",
    "Electric Power Natural Gas",
    "Electric Power Wood",
    "Industrial Coal",
    "Industrial Distillate Fuel Oil",
    "Industrial Geothermal",
    "Industrial Hydropower",
    "Industrial Kerosene",
    "Industrial Petroleum",
    "Industrial Natural Gas",
    "Industrial Other Petroleum Products",
    "Industrial Solar",
    "Industrial Wind",
    "Industrial Wood",
    "Refinery Coal",
    "Refinery Distillate Fuel",
    "Refinery Natural Gas",
    "Residential Coal",
    "Residential Distillate Fuel Oil",
    "Residential Geothermal",
    "Residential Kerosene",
    "Residential Petroleum",
    "Residential Natural Gas",
    "Residential Wood",
  ];
  strings.forEach((i) => {
    vector.push_back(i);
    var x = document.createElement("option");
    x.text = i;
    document.getElementById("cstype").add(x);
  });

  //create data source
  const ds = new Module.DataSet("energy.csv", vector);
  //populate states
  var stateNames = ds.GetStateList();
  for (var i = 0; i < stateNames.size(); i++) {
    var x = document.createElement("option");
    x.text = stateNames.get(i);
    document.getElementById("state").add(x);
  }

  //populate years
  var years = ds.GetYearList();
  for (var i = 0; i < years.size(); i++) {
    var x = document.createElement("option");
    x.text = years.get(i);
    document.getElementById("year").add(x);
  }

  //create temporary vectors to store sorted and unsorted data
  var dataVector;
  var unsortedVector;
  let sorted = false;

  //get access to elements from HTML
  let consumptionType = document.getElementById("cstype");
  let currentState = document.getElementById("state");
  let currentYear = document.getElementById("year");
  let mergeSortButton = document.getElementById("mergesort");
  let quickSortButton = document.getElementById("quicksort");
  let title = document.getElementById("titleVal");
  let resetTable = document.getElementById("reset-table");
  let resetSelections = document.getElementById("reset");
  let compareStructures = document.getElementById("compare");
  let sortText = document.getElementById("sort-text");
  //disable specific buttons
  mergeSortButton.disabled = true;
  quickSortButton.disabled = true;
  resetTable.disabled = true;
  resetSelections.disabled = true;
  compareStructures.disabled = true;

  //add event listeners
  consumptionType.addEventListener("change", stateHandle);
  currentState.addEventListener("change", stateHandle);
  currentYear.addEventListener("change", stateHandle);
  quickSortButton.addEventListener("click", handleQuickSort);
  mergeSortButton.addEventListener("click", handleMergeSort);
  resetTable.addEventListener("click", resetTableFunc);
  resetSelections.addEventListener("click", handleReset);
  compareStructures.addEventListener("click", handleCompare);

  //functiion to compare two datastructures
  function handleCompare() {
    var qsTime = handleQuickSort();
    stateHandle();
    var msTime = handleMergeSort();
    if (qsTime > msTime) {
      sortText.innerHTML = `Merge Sort was faster than Quick Sort by ${
        qsTime - msTime
      } ms`;
    }
    if (qsTime < msTime) {
      sortText.innerHTML = `Quick Sort was faster than Merge Sort by ${
        msTime - qsTime
      } ms`;
    }
  }

  //function to reset table
  function resetTableFunc() {
    loadTable(unsortedVector);
    resetTable.disabled = true;
    quickSortButton.disabled = false;
    mergeSortButton.disabled = false;
    sortText.classList.add("unsorted");
    sortText.innerHTML = "Unsorted";
    compareStructures.disabled = false;
  }

  //function to perform quick sort
  function handleQuickSort() {
    var a = performance.now();
    ds.quickSort(dataVector, 0, dataVector.size() - 1);
    loadTable(dataVector);
    var b = performance.now();
    sourted = true;
    quickSortButton.disabled = true;
    mergeSortButton.disabled = true;
    compareStructures.disabled = true;
    resetTable.disabled = false;
    sortText.innerHTML = `Successfully Sorted using Quick Sort in ${b - a} ms`;
    sortText.classList.remove("unsorted");
    return b - a;
  }

  //function to perform merge sort
  function handleMergeSort() {
    var a = performance.now();
    ds.mergeSort(dataVector, 0, dataVector.size() - 1);
    loadTable(dataVector);
    var b = performance.now();
    sorted = true;
    quickSortButton.disabled = true;
    compareStructures.disabled = true;
    mergeSortButton.disabled = true;
    resetTable.disabled = false;
    sortText.innerHTML = `Successfully Sorted using Quick Sort in ${b - a} ms`;
    sortText.classList.remove("unsorted");
    return b - a;
  }

  //function to handle state change
  function stateHandle() {
    var selectionCount = 0;
    if (currentState.value != "") {
      selectionCount++;
    }
    if (currentYear.value != "") {
      selectionCount++;
    }
    if (consumptionType.value != "") {
      selectionCount++;
    }
    if (selectionCount != 2) {
      $("#tablebody tr").remove();
      mergeSortButton.disabled = true;
      quickSortButton.disabled = true;
      resetTable.disabled = true;
      compareStructures.disabled = true;
    } else {
      if (
        consumptionType.value != "" &&
        currentState.value === "" &&
        currentYear.value != ""
      ) {
        dataVector = ds.getStates(consumptionType.value, currentYear.value);
        unsortedVector = ds.getStates(consumptionType.value, currentYear.value);
        title.innerHTML = "State";
        loadTable(dataVector);
      }
      if (
        consumptionType.value === "" &&
        currentState.value != "" &&
        currentYear.value != ""
      ) {
        dataVector = ds.getConsumptionTypes(
          currentState.value,
          Number(currentYear.value)
        );
        unsortedVector = ds.getConsumptionTypes(
          currentState.value,
          Number(currentYear.value)
        );
        title.innerHTML = "Consumption Type";
        loadTable(dataVector);
      }
      if (
        consumptionType.value != "" &&
        currentState.value != "" &&
        currentYear.value === ""
      ) {
        dataVector = ds.getYears(currentState.value, consumptionType.value);
        unsortedVector = ds.getYears(currentState.value, consumptionType.value);
        title.innerHTML = "Year";
        loadTable(dataVector);
      }
      if (
        consumptionType.value === "" &&
        currentState.value === "" &&
        currentYear.value === ""
      ) {
        title.innerHTML = "";
      }
      mergeSortButton.disabled = false;
      quickSortButton.disabled = false;
      compareStructures.disabled = false;
    }
    if (selectionCount === 0) {
      title.innerHTML = "";
      resetSelections.disabled = true;
    } else {
      resetSelections.disabled = false;
    }
  }

  //load table
  function loadTable(data) {
    $("#tablebody tr").remove();
    const table = document.getElementById("tablebody");
    for (var i = 0; i < data.size(); i++) {
      let row = table.insertRow();
      let name = row.insertCell(0);
      name.innerHTML = data.get(i)[0];
      let value = row.insertCell(1);
      value.innerHTML = data.get(i)[1];
    }
  }

  //handle resetting selection
  function handleReset() {
    title.innerHTML = "";
    $("#tablebody tr").remove();
    document.getElementById("reset").disabled = true;
    quickSortButton.disabled = true;
    compareStructures.disabled = true;
    mergeSortButton.disabled = true;
    sortText.innerHTML = "Unsorted";
    sortText.classList.add("unsorted");
    consumptionType.value = "";
    currentState.value = "";
    currentYear.value = "";
  }
});
