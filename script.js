const SELECTIONS = [
    {
        name: 'rock',
        emoji: '✊',
        beats: 'scissors',
    },
    {
        name: 'paper',
        emoji: '🤚',
        beats: 'rock',
    },
    {
        name: 'scissors',
        emoji: '✌️',
        beats: 'paper',
    }
];
const selectionButtons = document.querySelectorAll('[data-selection]');
const finalColumn = document.querySelector('[data-final-column]');
const computerScore = document.querySelector('[data-computer-score]');
const playerScore = document.querySelector('[data-player-score]');  

function computerSelection() {
    const randIdx = Math.floor(Math.random() * SELECTIONS.length);
    return SELECTIONS[randIdx];
}

function makeSelection(selection) {
    const computerSelect = computerSelection();
    const playerWins = isWinner(selection, computerSelect);
    const computerWins = isWinner(computerSelect, selection);
    addResult(computerSelect, computerWins);
    addResult(selection, playerWins);
    if(playerWins) incrementScore(playerScore);
    if(computerWins) incrementScore(computerScore);
}

function addResult(selection, wins) {
    const div = document.createElement('div');
    div.innerText = selection.emoji;
    div.classList.add('result-selection');
    if (wins) {
        div.classList.add('winner');
    }
    finalColumn.after(div);
}

function isWinner(selection, computerSelect) {
    return selection.beats === computerSelect.name;
}

function incrementScore(score) {
    score.innerText = parseInt(score.innerText) + 1;
}



selectionButtons.forEach(selectionButton => {
    selectionButton.addEventListener('click', e => {
        const selectionName = selectionButton.dataset.selection;
        const selection = SELECTIONS.find(selection => selection.name === selectionName);
        makeSelection(selection);
    });
})