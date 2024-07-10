class MyButton extends HTMLElement {
  constructor() {
    super(); // 调用父类的构造函数
    this.attachShadow({ mode: 'open' }); // 创建 Shadow DOM
  }

  click() {
    alert('Hello, World!');
  }

  connectedCallback() {
    this.render();
    this.shadowRoot.querySelector('button').addEventListener('click', () => this.click());
  }

  render() {
    this.shadowRoot.innerHTML = `
          <style>
            button {
              padding: 10px 20px;
              border: none;
              border-radius: 5px;
              background-color: #007BFF;
              color: white;
              cursor: pointer;
            }
          </style>
          <button>
            <slot></slot> <!-- 使用 slot 分发内容 -->
          </button>
        `;
  }
}
customElements.define('my-button', MyButton);