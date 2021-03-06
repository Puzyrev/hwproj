package puzyrev.sem2.hw2.task2;

/**
 * Double linked List class.
 */
public class DoubleLinkedList implements List {
    private Element first = null;
    private Element last = null;

    public void addValue(int value) {
        if (isEmpty()) {
            first = new Element(value, null, null);
            last = first;
            return;
        }

        if (value < first.value) {
            first = new Element(value, first, null);
            return;
        }

        Element temp = first;
        while (temp.next != null && value > temp.next.value) {
            temp = temp.next;
        }
        Element toAdd = new Element(value, temp.next, temp);
        temp.next = toAdd;
        if (temp.next.next != null)
            temp.next.next.prev = toAdd;
        if (temp.next.next == null)
            last = toAdd;
    }

    public void deleteValue(int value) {
        if (isEmpty())
            return;

        Element temp = first;
        if (temp.next == null && temp.value == value) {
            first = null;
            last = null;
            return;
        }

        if (temp.value == value) {
            first = temp.next;
            temp.next.prev = null;
            return;
        }

        while (temp.next != null && temp.next.value != value) {
            temp = temp.next;
        }
        if (temp.next == null)
            return;

        temp.next = temp.next.next;
        if (temp.next != null)
            temp.next.prev = temp;
        if (temp.next == null)
            last = temp;
    }

    public boolean isEmpty() {
        return first == null;
    }

    public void print() {
        Element temp = first;
        while (temp != null) {
            System.out.print(temp.value + " ");
            temp = temp.next;
        }
        System.out.println();
    }

    /**
     * List element class.
     */
    private class Element {
        private int value;
        private Element next;
        private Element prev;

        public Element(int value, Element next, Element prev) {
            this.value = value;
            this.next = next;
            this.prev = prev;
        }
    }
}