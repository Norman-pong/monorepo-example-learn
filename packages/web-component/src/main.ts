import './myButton.ts'
import './reactiveItem.ts'

const app = document.querySelector('#app') as HTMLElement

const button = document.createElement('my-button')
button.appendChild(document.createTextNode('Click me!'))

app.appendChild(button)
app.appendChild(document.createElement('reactive-item'))

const icon = document.createElement('iconpark-icon')
icon.setAttribute('name', 'item-close')

app.appendChild(icon)