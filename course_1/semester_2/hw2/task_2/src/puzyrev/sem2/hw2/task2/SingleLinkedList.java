package puzyrev.sem2.hw2.task2;

/**
 * Single linked List class.
 */
public class SingleLinkedList implements List {
    private Element first = null;

    public void addValue(int value) {
        if (isEmpty()) {
            first = new Element(value, null);
            return;
        }

        if (value < first.value) {
            first = new Element(value, first);
            return;
        }

        Element temp = first;
        while (temp.next != null && value > temp.next.value) {
            temp = temp.next;
        }
        temp.next = new Element(value, temp.next);
    }

    public void deleteValue(int value) {
        if (isEmpty())
            return;

        Element temp = first;
        if (temp.next == null && temp.value == value) {
            first = null;
            return;
        }

        if (temp.value == value) {
            first = temp.next;
            return;
        }

        while (temp.next != null && temp.next.value != value) {
            temp = temp.next;
        }
        if (temp.next == null)
            return;

        temp.next = temp.next.next;
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

        public Element(int value, Element next) {
            this.value = value;
            this.next = next;
        }
    }
}