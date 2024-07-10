function reactive(data) {
  return new Proxy(data, {
    get(target, property, receiver) {
      return Reflect.get(target, property, receiver);
    },
    set(target, property, value, receiver) {
      target[property] = value;
      // 假设有一个方法来更新 DOM
      updateDOM();
      return true;
    }
  });
}

function updateDOM() {
  console.log('DOM')
  // 更新 DOM 的逻辑
}

class ReactiveComponent extends HTMLElement {
  constructor() {
    super();
    this.attachShadow({ mode: 'open' });
  }

  connectedCallback() {
    this.data = reactive({ count: 0 });
    this.shadowRoot.innerHTML = `
            <style>
              /* 样式 */
            </style>
            <div>Count: <span id="count"></span></div>
            <button id="increment">Increment</button>
          `;
    this.shadowRoot.querySelector('#count').textContent = this.data.count;
    this.shadowRoot.querySelector('#increment').addEventListener('click', () => {
      this.data.count++; // 这将触发 DOM 更新
      // this.shadowRoot.querySelector('#count').textContent = this.data.count;
      console.log(this.data.count);
    });
  }
}

customElements.define('reactive-item', ReactiveComponent);